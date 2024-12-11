/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
 * @Files:user_bmi270.c/h
 * 
 * @Author: Ye Jinyi
 * 
 * @First  Edit Date: 2014.11.16
 * @Latest Edit Date: 2014.11.17
 * 
 * @illustrate: 与bmi2.c bmi270.c 共同构成bmi270的驱动，与其他部分独立
 *              bmi2.c/h bmi270.c/h bmi2_defs.h是博世官方的驱动，在https://github.com/boschsensortec/BMI270_SensorAPI
 *              本文件创建bmi270实例并连接接口，实现初始化和原始数据的读取
 *              操作的结构体：bmi_hardware_t bmi_hardware
 * 
 * @attention: 本工程不需要温度数据所以不读。
 *             注意注意！小主控的spi2通信速率不稳定，建议调低一点，分频系数在32为宜，否则会有很多bug
 * 
 * @Copyright: RobotPilots-YJY
 *-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Including Files -------------------------------------------------------------------------------------------------------------------------------------------------- */
#include "drv_bmi270.h"

/* External Variables Declarations ---------------------------------------------------------------------------------------------------------------------------------- */
extern SPI_HandleTypeDef hspi3;

/* Define Exported Variables ---------------------------------------------------------------------------------------------------------------------------------------- */
/*创建bmi实例*/
bmi_hardware_t bmi_hardware = 
{
    .init = &bmi270_hardware_init,
    .read_raw_data = &bmi270_read_hardware_data,
    .get_real_data = &bmi270_get_real_data,
};

/* Define Privated Variables ---------------------------------------------------------------------------------------------------------------------------------------- */


/* Define Privated Functions ---------------------------------------------------------------------------------------------------------------------------------------- */
/*!
 * @usage: Delay function map to bmi270
 */
uint32_t bmi2_micros(void)
{
    register uint32_t bms, bus;
    static uint32_t btick = 0;
    
    bms = HAL_GetTick();
    
    bus = TIM2->CNT;
    
    btick = bms*1000 + bus;
    
    return btick;
} 

void bmi2_delay_us(uint32_t period, void *intf_ptr)
{
    uint32_t now = bmi2_micros();
    
    while((bmi2_micros() - now) < period)
    {
    }
}

void bmi2_delay(uint32_t ms)
{
    while(ms--)
    {
        bmi2_delay_us(1000,NULL);
    }
}

/*!
 * @usage:SPI read function map to COINES platform
 */
BMI2_INTF_RETURN_TYPE bmi2_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t res;
    
//    __SPI_CS_LOW();
//    HAL_SPI_Transmit(&hspi3, &reg_addr, 1, 1000);
//    res = HAL_SPI_Receive(&hspi3, reg_data, len, 1000);
//    __SPI_CS_HIGH();
    
    return res;
    
}

/*!
 * @usage:SPI write function map to COINES platform
 */
BMI2_INTF_RETURN_TYPE bmi2_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t res;
    
//    __SPI_CS_LOW();
//    HAL_SPI_Transmit(&hspi3, &reg_addr, 1, 1000);
//    res = HAL_SPI_Transmit(&hspi3, (uint8_t *)reg_data, len, 1000);
//    __SPI_CS_HIGH();
    return res;
}

/*!
 *  @brief Function to init the SPI interface 
 *  Also to initialize coines platform
 */
int8_t bmi2_interface_init(struct bmi2_dev *bmi)
{
    int8_t rslt = BMI2_OK;
    
    if(bmi != NULL)
    {
        /* Bus configuration : SPI */
        /* To initialize the user SPI function */
        bmi->intf = BMI2_SPI_INTF;
        bmi->read = bmi2_spi_read;
        bmi->write = bmi2_spi_write;
        
        /* Configure delay in microseconds */
        bmi->delay_us = bmi2_delay_us;

        /* Configure max read/write length (in bytes) ( Supported length depends on target machine) */
        bmi->read_write_len = READ_WRITE_LEN;

        /* Assign to NULL to load the default config file. */
        bmi->config_file_ptr = NULL;

        bmi2_delay(100);

    }
    else
    {
        rslt = BMI2_E_NULL_PTR;
    }

    return rslt;

}

/* Define Exported Functions ---------------------------------------------------------------------------------------------------------------------------------------- */
/*!
 * @usage:初始化bmi270
 */
int8_t bmi270_hardware_init(bmi_hardware_t *bmi_hardware)
{
    int8_t rslt;

    // 初始化接口
    bmi2_interface_init(&bmi_hardware->bmi270);

    // 初始化 BMI270
    rslt = bmi270_init(&bmi_hardware->bmi270);
    if (rslt == BMI2_OK) {
        // 使能加速度计和陀螺仪传感器
        uint8_t sensor_list[2] = {BMI2_ACCEL, BMI2_GYRO};
        rslt = bmi270_sensor_enable(sensor_list, 2, &bmi_hardware->bmi270);
        
        // 配置加速度计参数
        struct bmi2_sens_config config[2];
        config[0].type = BMI2_ACCEL;
        rslt = bmi270_get_sensor_config(&config[0], 1, &bmi_hardware->bmi270);
        if (rslt == BMI2_OK)
        {
            config[0].cfg.acc.bwp = BMI2_ACC_OSR4_AVG1;   // 最小滤波，最快响应，噪声较高
            config[0].cfg.acc.odr = BMI2_ACC_ODR_1600HZ;  // 设置输出数据速率为 1600Hz
            config[0].cfg.acc.range = BMI2_ACC_RANGE_2G;  // 设置量程为 ±2G
            rslt = bmi270_set_sensor_config(&config[0], 1, &bmi_hardware->bmi270);
        }

        // 配置陀螺仪参数
        config[1].type = BMI2_GYRO;
        rslt = bmi270_get_sensor_config(&config[1], 1, &bmi_hardware->bmi270);
        if (rslt == BMI2_OK)
        {
            config[1].cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;  // 最低延迟，最快响应，噪声较高
            config[1].cfg.gyr.odr = BMI2_GYR_ODR_1600HZ;   // 设置输出数据速率为 1600Hz
            config[1].cfg.gyr.range = BMI2_GYR_RANGE_1000; // 设置量程为 ±1000 dps
            rslt = bmi270_set_sensor_config(&config[1], 1, &bmi_hardware->bmi270);
        }
        
        
    }

    return rslt;
}

/*!
 * @usage:读取加速度计和陀螺仪原始数据，存在bmi_sensor结构体
 */
int8_t bmi270_read_hardware_data(bmi_hardware_t *bmi_hardware)
{
    int8_t rslt;
    
    // 读取加速度和陀螺仪数据数据
    rslt = bmi2_get_sensor_data(&bmi_hardware->raw_data, &bmi_hardware->bmi270);
    
    return rslt;
}

/*!
 * @usage:获取取加速度计和陀螺仪真实数据
 */
void bmi270_get_real_data(float gyro[], float accel[], float *temperature)
{
    bmi270_read_hardware_data(&bmi_hardware);
    
    //原始数据*灵敏度
    //单位rad/s
    bmi_hardware.real_data.gyro[0] = ((float)bmi_hardware.raw_data.gyr.x) * BMI270_GYRO_SEN;
    bmi_hardware.real_data.gyro[1] = ((float)bmi_hardware.raw_data.gyr.y) * BMI270_GYRO_SEN;
    bmi_hardware.real_data.gyro[2] = ((float)bmi_hardware.raw_data.gyr.z) * BMI270_GYRO_SEN;
    
    //单位m/s^2
    bmi_hardware.real_data.accel[0] = ((float)bmi_hardware.raw_data.acc.x) * BMI270_ACCEL_SEN * GRAVITY;
    bmi_hardware.real_data.accel[1] = ((float)bmi_hardware.raw_data.acc.y) * BMI270_ACCEL_SEN * GRAVITY;
    bmi_hardware.real_data.accel[2] = ((float)bmi_hardware.raw_data.acc.z) * BMI270_ACCEL_SEN * GRAVITY;
    
    //用不到温度，给个常数
    bmi_hardware.real_data.temperature = 37;
    
    gyro[0] = bmi_hardware.real_data.gyro[0];
    gyro[1] = bmi_hardware.real_data.gyro[1];
    gyro[2] = bmi_hardware.real_data.gyro[2];
    accel[0] = bmi_hardware.real_data.accel[0];
    accel[1] = bmi_hardware.real_data.accel[1];
    accel[2] = bmi_hardware.real_data.accel[2];
    *temperature = bmi_hardware.real_data.temperature;
    
}


void Drv_Bmi270_Init(void)
{

  bmi270_hardware_init(&bmi_hardware);
}
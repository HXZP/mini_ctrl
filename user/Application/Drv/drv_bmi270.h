#ifndef DRV_BMI270_H
#define DRV_BMI270_H

/* Including Files -------------------------------------------------------------------------------------------------------------------------------------------------- */
#include "stm32f1xx_hal.h"
#include "main.h"
#include "bmi2.h"
#include "bmi270.h"
#include "bmi2_defs.h"

/* Macro ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
#define __SPI_CS_HIGH()   do{ HAL_GPIO_WritePin(BMI270_SPI2_CS_GPIO_Port, BMI270_SPI2_CS_Pin, GPIO_PIN_SET);   }while(0)
#define __SPI_CS_LOW()    do{ HAL_GPIO_WritePin(BMI270_SPI2_CS_GPIO_Port, BMI270_SPI2_CS_Pin, GPIO_PIN_RESET); }while(0)

#define READ_WRITE_LEN     UINT8_C(46)      //Macro that defines read write length

#define BMI270_ACCEL_2G_SEN 0.0000610351563f
#define BMI270_ACCEL_4G_SEN 0.0001220703126f

#define BMI270_GYRO_2000_SEN 0.00106526443603169529841533860381f
#define BMI270_GYRO_1000_SEN 0.00053263221801584764920766930190693f
#define BMI270_GYRO_500_SEN 0.00026631610900792382460383465095346f
#define BMI270_GYRO_250_SEN 0.00013315805450396191230191732547673f
#define BMI270_GYRO_125_SEN 0.000066579027251980956150958662738366f

//用户用到的
#define GRAVITY 9.78f
#define BMI270_ACCEL_SEN BMI270_ACCEL_2G_SEN
#define BMI270_GYRO_SEN BMI270_GYRO_1000_SEN

/* Define Exported Variables Type ----------------------------------------------------------------------------------------------------------------------------------- */
typedef struct bmi270_real_data_struct
{
    float accel[3];
    float gyro[3];
    float temperature;
} bmi270_real_data_t;

/*bmi驱动层结构体*/
typedef struct bmi_hardware_struct
{
    struct bmi2_dev         bmi270;
    struct bmi2_sens_data   raw_data;
    bmi270_real_data_t      real_data;
    
    int8_t (*init)(struct bmi_hardware_struct *bmi_sensor);
    int8_t (*read_raw_data)(struct bmi_hardware_struct *bmi_sensor);
    void   (*get_real_data)(float gyro[], float accel[], float *temperature);
}bmi_hardware_t;

/* Define Privated Variables Type ----------------------------------------------------------------------------------------------------------------------------------- */


/* Exported Variables Declarations ---------------------------------------------------------------------------------------------------------------------------------- */
extern bmi_hardware_t bmi_hardware;

/* Exported Functions Declarations ---------------------------------------------------------------------------------------------------------------------------------- */
int8_t bmi270_hardware_init(bmi_hardware_t *bmi_sensor);
int8_t bmi270_read_hardware_data(bmi_hardware_t *bmi_sensor);
void bmi270_get_real_data(float gyro[], float accel[], float *temperature);
void Drv_Bmi270_Init(void);
#endif

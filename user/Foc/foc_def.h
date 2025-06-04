#ifndef __FOC_DEF_H 
#define __FOC_DEF_H

#include "math.h"
#include "stdint.h"

/*
分析上，从电压矢量分解到相位电压矢量，再分解到Clarke坐标下的静止坐标系，再分解到Park坐标下的旋转坐标系得到d轴和q轴的电压矢量。
电机的力来自磁力，磁力由电流产生，电流由电压产生，电压由电压矢量产生，最后输出的就是能够控制电压矢量的控制时间。

在控制上，控制目标值q轴的电压矢量，再反方向分解到Park坐标下的旋转坐标系，再反方向分解到Clarke坐标下的静止坐标系，再反方向分解到相位电压矢量，最后输出控制时间。
控制电压矢量通过控制七个基本电压矢量的开启时间来实现，并且这六个基本电压矢量将一圈分为六个区，目标矢量在一个区中只需要两个基本矢量就能合成，所以最后只需要控制两个基本矢量的时间。
分区的位置可以通过目标矢量知道

*/
#define FOC_PI 3.14159265f
#define SQRT_3 0.86602540f

typedef enum{
    
    Foc_Zero_Angle_Init,
    Foc_Working,
}foc_state_e;

typedef struct{

    float a;
    float b;
    float c;
}foc_phase_volage_t;

typedef struct{

    float a;
    float b;
    float c;
}foc_phase_current_t;

typedef struct{

    float d;
    float q;
    float theta;
}foc_park_t;

typedef struct{

    float alpha;
    float beta;
}foc_clarke_t;

typedef struct{

    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t N;
    uint8_t value;
}foc_sector_t;

//向量的号码和开启的半桥是对应的ABC对于位为高中低
typedef struct{

    float strength;//0~vector_voltage
    union{
        uint8_t value;//0~7
        struct{

            uint8_t Sc:1;
            uint8_t Sb:1;
            uint8_t Sa:1; 
            uint8_t res:5;       
        }half_bridge;
    }direction;

    float percent;//0~100
}foc_vector_t;

typedef struct{

    float X;
    float Y;
    float Z;
}foc_vector_percent_t;

typedef struct{

    foc_vector_t vector_x;  
    foc_vector_t vector_y;
    foc_vector_t vector_0;
    foc_vector_t vector_7;
}foc_output_vector_t;

//range:0-T
typedef struct{

    uint16_t T;
    uint16_t a;
    uint16_t b;
    uint16_t c;
}foc_pwm_duty_t;

typedef struct{

    float sensor_angle;
    float zero_angle;
    float elec_angle;
    float mech_angle;
}foc_angle_sensor_t;

typedef struct{

    float master_voltage;//母线电压
    float vector_voltage;//基本电压矢量:0~母线电压/sqrt(3)
    uint8_t pole_pairs;//极对数
}foc_mechine_info_t;

typedef struct{

    foc_state_e state;
    foc_mechine_info_t info;

    foc_phase_volage_t phase_volage;
    foc_phase_current_t phase_current;
    
    foc_clarke_t       clarke;
    foc_park_t         park;
    foc_sector_t       sector;
    foc_output_vector_t output_vector;
    foc_vector_percent_t vector_percent;
    foc_pwm_duty_t      pwm_duty;

    foc_angle_sensor_t  angle;

    foc_park_t         target_park;

}foc_t;

typedef struct{
    
    foc_state_e state;
    uint8_t pole_pairs;//极对数
    float master_voltage;//母线电压
    float zero_angle;
    uint16_t pwm_period;
    uint16_t pwm_ccr;
}foc_cfg_t;




#endif /* __FOC_DEF_H */

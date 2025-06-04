/*
    基于SVPWM的FOC算法实现

*/
#include "foc_core.h"

/*
    **  @brief  N值到扇区
*/
uint8_t N2sector[6] = {2,6,1,4,3,5};
/*
    **  @brief  扇区到两个子向量 顺序为扇区的逆时针方向
*/
uint8_t sector2vector[6][2] = {
    {4, 6},
    {6, 2},
    {2, 3},
    {3, 1},
    {1, 5}
};
/*
    **  @brief  从扇区到两个基向量的加权 顺序为扇区的逆时针方向
*/
int8_t sector2vector_mask[6][2][3] = {
    {{0,0,-1},{1,0,0}},
    {{0,0,1},{0,1,0}},
    {{1,0,0},{0,-1,0}},
    {{-1,0,0},{0,0,1}},
    {{0,-1,0},{0,0,-1}},
    {{0,1,0},{-1,0,0}}
};
/*
    **  @brief  基本模型
*/
/*
    **  @brief  Clarke变换
                a-b-c和α-β的关系
*/
void foc_clarke(foc_clarke_t *clarke, const foc_phase_volage_t *phase_volage)
{
    clarke->alpha = (phase_volage->a - phase_volage->b - phase_volage->c)*2/3;
    clarke->beta = (phase_volage->b - phase_volage->c)/SQRT_3;
}
/*
    **  @brief  Park变换
                α-β和d-q的关系
*/
void foc_park(foc_park_t *park, const foc_clarke_t *clarke)
{
    park->d = clarke->alpha * cos(park->theta) + clarke->beta * sin(park->theta);
    park->q =-clarke->alpha * sin(park->theta) + clarke->beta * cos(park->theta);
}
/*
    **  @brief  反Clarke变换
                α-β和a-b-c的关系
*/
void foc_reclarke(foc_clarke_t *clarke, const foc_phase_volage_t *phase_volage)
{
    phase_volage->a = clarke->alpha;
    phase_volage->b = -clarke->alpha/2 + clarke->beta * SQRT_3/2;
    phase_volage->c = -clarke->alpha/2 - clarke->beta * SQRT_3/2;
}
/*
    **  @brief  反Park变换
                d-q和α-β的关系
*/
void foc_repark(foc_clarke_t *clarke, const foc_park_t *park)
{
    clarke->alpha = park->d * cos(park->theta) - park->q * sin(park->theta);
    clarke->beta = park->d * sin(park->theta) + park->q * cos(park->theta);
}

/*
    **  @brief  扇区判断,根据向量落点对于三根直线的关系获取扇区,本质上的是判断向量落在哪个象限
*/
void foc_get_sector(foc_sector_t *sector, const foc_clarke_t *clarke)
{
    if(clarke->beta > 0)
    {
        sector->A = 1
    }
    else
    {
        sector->A = 0;
    }
    
    if(SQRT_3 * clarke->alpha - clarke->beta > 0)
    {
        sector->B = 1;
    }
    else
    {
        sector->B = 0;
    }

    if(-SQRT_3 * clarke->alpha - clarke->beta > 0)
    {
        sector->C = 1;
    }
    else
    {
        sector->C = 0;
    }

    sector->N = 4 * sector->C + 2 * sector->B + sector->A;
    sector->value = N2sector[sector->N];
}

void foc_get_vector_percent(foc_vector_percent_t *vector_percent, const float vector_voltage, const foc_clarke_t *clarke)
{
    vector_percent->X = clarke->beta/vector_voltage * 100;
    vector_percent->Y = (clarke->alpha * SQRT_3/2 + clarke->beta/2) /vector_voltage * 100;
    vector_percent->Z = (-clarke->alpha * SQRT_3/2 + clarke->beta/2) /vector_voltage * 100;
}

void foc_get_vector_normalize(foc_output_vector_t *vector, const foc_vector_percent_t *vector_percent, const foc_sector_t *sector)
{
    float percent_x = 0;
    float percent_y = 0;

    percent_x = sector2vector_mask[sector->value][0][0] * vector_percent->X
                + sector2vector_mask[sector->value][0][1] * vector_percent->Y
                    + sector2vector_mask[sector->value][0][2] * vector_percent->Z;

    percent_y = sector2vector_mask[sector->value][1][0] * vector_percent->X
                + sector2vector_mask[sector->value][1][1] * vector_percent->Y
                    + sector2vector_mask[sector->value][1][2] * vector_percent->Z;

    if(percent_x + percent_y > 100)
    {
        vector->vector_x.percent = percent_x/(percent_x + percent_y) * 100;
        vector->vector_y.percent = percent_y/(percent_x + percent_y) * 100;
    }                
    else
    {
        vector->vector_x.percent = percent_x;
        vector->vector_y.percent = percent_y;
    }
    vector->vector_0.percent = (100 - percent_x - percent_y)/2;
    vector->vector_7.percent = (100 - percent_x - percent_y)/2;

    vector->vector_x.direction.value = sector2vector[sector->value + 1][0];
    vector->vector_y.direction.value = sector2vector[sector->value + 1][1];
    vector->vector_0.direction.value = 0;
    vector->vector_7.direction.value = 7;
}

void foc_get_vector_strength(foc_output_vector_t *vector, const float vector_voltage)
{
    vector->vector_x.strength = vector->vector_x.percent * vector_voltage/100;
    vector->vector_y.strength = vector->vector_y.percent * vector_voltage/100;
    vector->vector_0.strength = vector->vector_0.percent * vector_voltage/100;
    vector->vector_7.strength = vector->vector_7.percent * vector_voltage/100;
}

void foc_get_pwm_duty(foc_pwm_t *pwm, const foc_output_vector_t *vector)
{
    pwm->a = (vector->vector_x.percent * vector->vector_x.direction.half_bridge.Sa
            + vector->vector_y.percent * vector->vector_y.direction.half_bridge.Sa
            + vector->vector_0.percent * vector->vector_0.direction.half_bridge.Sa
            + vector->vector_7.percent * vector->vector_7.direction.half_bridge.Sa) * pwm->T;

    pwm->b = (vector->vector_x.percent * vector->vector_x.direction.half_bridge.Sb
            + vector->vector_y.percent * vector->vector_y.direction.half_bridge.Sb
            + vector->vector_0.percent * vector->vector_0.direction.half_bridge.Sb
            + vector->vector_7.percent * vector->vector_7.direction.half_bridge.Sb) * pwm->T;

    pwm->c = (vector->vector_x.percent * vector->vector_x.direction.half_bridge.Sc
            + vector->vector_y.percent * vector->vector_y.direction.half_bridge.Sc
            + vector->vector_0.percent * vector->vector_0.direction.half_bridge.Sc
            + vector->vector_7.percent * vector->vector_7.direction.half_bridge.Sc) * pwm->T;
}











float foc_angle_cycle(float angle)
{
    if(angle > 2 * PI)
    {
        return angle - 2 * PI;
    }
    else if(angle < 0)
    {
        return angle + 2 * PI;
    }
    else
    {
        return angle;
    }
}





void foc_init(foc_t *foc, foc_cfg_t *cfg)
{
    foc->info.vector_voltage = foc->info.voltage/SQRT_3;
}

void foc_sensor_updata(foc_t *foc, float angle)
{
    foc->angle.sensor_angle = angle;
    foc->angle.mech_angle = foc_angle_cycle(angle - foc->angle.zero_angle);
    foc->angle.elec_angle = foc->angle.mech_angle * foc->info.pole_pairs;

    
}

void foc_target_updata(foc_t *foc, foc_park_t *target)
{
    // if(target->d * target->d + target->q * target->q > foc->info.vector_voltage * foc->info.vector_voltage)
    // {
    //     // 如果目标电压的平方和大于最大电压的平方和，则将目标电压限制在最大电压范围内
    // }

    foc->target_park = target;


}

void foc_zero_angle_updata(foc_t *foc)
{
    foc->angle.zero_angle = foc->angle.elec_angle;
}

void foc_control(foc_t *foc)
{
    if(foc->state == Foc_Zero_Angle_Init)
    {
        foc->park.d = foc->info.vector_voltage;
        foc->park.q = 0;
        foc->park.theta = 0;
    }
    else if(foc->state == Foc_Working)
    {
        foc->park.d = foc->target_park.d;
        foc->park.q = foc->target_park.q;
        foc->park.theta = foc->angle.elec_angle;
    }

    foc_repark(&foc->clarke, &foc->park);
    foc_get_sector(&foc->sector, &foc->clarke);
    foc_get_vector_percent(&foc->vector_percent, &foc->info.vector_voltage, &foc->clarke);
    foc_get_vector_normalize(&foc->vector, &foc->vector_percent, &foc->sector);
    foc_get_vector_strength(&foc->vector, &foc->info.vector_voltage);
    foc_get_pwm_duty(&foc->pwm, &foc->vector);
}



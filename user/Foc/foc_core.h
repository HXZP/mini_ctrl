#ifndef __FOC_CORE_H
#define __FOC_CORE_H

#include "foc_def.h"




void foc_init(foc_t *foc, const foc_cfg_t *cfg);
void foc_sensor_updata(foc_t *foc, float angle);
void foc_target_updata(foc_t *foc, foc_park_t target);
void foc_zero_angle_updata(foc_t *foc);
void foc_control(foc_t *foc);









#endif /* __FOC_CORE_H */








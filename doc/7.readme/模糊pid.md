# 模糊pid

![image-20250301145223471](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301145223471.png)

![image-20250301145230465](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301145230465.png)

## 模糊控制器：

输入：e、ec

输出：kp、ki、kd

全过程输入输出：

对Kp

在![image-20250301151428922](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301151428922.png)中寻找e、ec最接近的两个值，然后按接近度得到两个隶属值

一共可以得到四个值：隶属值a和1-a、隶属值b和1-b

隶属值再按矩阵乘法得到四个值，再和表中对应的四个值进行加权乘法，用这个四个值进行调整Kp

其余同等操作





e通过隶属度得到![image-20250301151428922](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301151428922.png)中两个隶属值a和1-a

ec通过隶属度得到![image-20250301151428922](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301151428922.png)中两个隶属值b和1-b





![image-20250301150423268](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250301150423268.png)

```C
typedef struct {
    // PID基础参数
    float Kp, Ki, Kd;
    float integral;   // 积分累积量
    float prev_error; // 上一次误差
    
    // 模糊控制相关参数
    float error_range;       // 误差论域范围（如-50℃~+50℃）
    float deltaKp, deltaKi, deltaKd; // 参数调整量
    float (*membership_e)[3];  // 误差隶属度函数参数（示例：三角形函数中心点）
    float (*membership_ec)[3]; // 误差变化率隶属度函数
    int rule_base[7][7][3];    // 模糊规则库[误差][误差变化率][ΔKp,ΔKi,ΔKd]
} FuzzyPID;

void init_membership(FuzzyPID *pid) {
    // 误差(e)模糊集：NB(负大), NM(负中), NS(负小), ZO(零), PS, PM, PB
    //分别对应pid的三个值
    float e_mf[7][3] = {
        {-50, -50, -30}, // NB
        {-50, -30, -10}, // NM
        {-30, -10, 0},   // NS
        {-10, 0, 10},    // ZO
        {0, 10, 30},     // PS
        {10, 30, 50},    // PM
        {30, 50, 50}     // PB
    };
    
    // 误差变化率(ec)同理
    memcpy(pid->membership_e, e_mf, sizeof(e_mf));
}

float calculate_membership(float x, float a, float b, float c) {
    // 三角形隶属度计算
    if (x <= a || x >= c) return 0.0f;
    return (x <= b) ? (x - a)/(b - a) : (c - x)/(c - b);
}

void fuzzify(FuzzyPID *pid, float e, float ec, float *mf_e, float *mf_ec) {
    // 计算误差和误差变化率的隶属度
    for(int i=0; i<7; i++) {
        mf_e[i] = calculate_membership(e, pid->membership_e[i][0], 
                                      pid->membership_e[i][1], 
                                      pid->membership_e[i][2]);
        // ec同理...
    }
}

void fuzzy_inference(FuzzyPID *pid, float *mf_e, float *mf_ec) {
    float deltaKp = 0.0f, deltaKi = 0.0f, deltaKd = 0.0f;
    float total_weight = 0.0f;
    
    // 遍历所有规则
    for(int i=0; i<7; i++) {
        for(int j=0; j<7; j++) {
            float weight = mf_e[i] * mf_ec[j]; // 规则激活度
            if(weight > 0) {
                deltaKp += weight * pid->rule_base[i][j][0];
                deltaKi += weight * pid->rule_base[i][j][1];
                deltaKd += weight * pid->rule_base[i][j][2];
                total_weight += weight;
            }
        }
    }
    
    // 重心法解模糊
    if(total_weight > 0) {
        pid->deltaKp = deltaKp / total_weight;
        pid->deltaKi = deltaKi / total_weight;
        pid->deltaKd = deltaKd / total_weight;
    }
}

float fuzzy_pid_update(FuzzyPID *pid, float setpoint, float actual, float dt) {
    // 计算误差
    float error = setpoint - actual;
    float ec = (error - pid->prev_error) / dt;
    
    // 模糊化
    float mf_e[7], mf_ec[7];
    fuzzify(pid, error, ec, mf_e, mf_ec);
    
    // 模糊推理
    fuzzy_inference(pid, mf_e, mf_ec);
    
    // 调整PID参数（带限幅）
    pid->Kp = fmax(0.1f, fmin(5.0f, pid->Kp + pid->deltaKp));
    pid->Ki = fmax(0.001f, fmin(0.5f, pid->Ki + pid->deltaKi));
    pid->Kd = fmax(0.0f, fmin(2.0f, pid->Kd + pid->deltaKd));
    
    // PID计算
    pid->integral += error * dt;
    float derivative = ec;
    float output = pid->Kp * error 
                 + pid->Ki * pid->integral 
                 + pid->Kd * derivative;
    
    // 输出限幅（0-100%）
    output = fmax(0.0f, fmin(100.0f, output));
    
    pid->prev_error = error;
    return output;
}
```


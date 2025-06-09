#include "stm32f10x.h"                  // Device header
#include <math.h>
#include <stdio.h>
#include "pwm.h"
#include "Delay.h"
#include "DFOC.h"
#include "AS5600.h"
#include "Serial.h"
#include "AD.h"
#include "Inlinecurrent.h"

#include "foc_core.h"

//#define    PI    3.14159265359f

//float Target = 0.0;
//float angle = 0.0;
//struct CurrentDetect Current;
//int main(void)
//{
//  Serial_Init(115200);
//	FOC_Init(12.6);

//	Systick_CountMode();  //��ʼ����શ�ʱ��

//	while(1)
//	{
//    Current = GetPhaseCurrent();
//    Serial_Printf("%f,%f,%f\n",Current.I_a,Current.I_b,Current.I_b+Current.I_a);
///***********�Ƕȴ�ӡ***********/
//		Serial_SendFloatNumber(GetAngle(),4, 2);	
//		Serial_SendString("\n");
///***********��������***********/
//		Target = GetCommand();
//		Set_CurTorque(Target);    //����ģʽ
//		
//	}
//	
//}

#define TASK_DELAY_MS 1
uint16_t task_cnt;

#define ZERO_DELAY_MS 1000
uint16_t zero_cnt;

void TIM1_Init(void);
void TIM2_Init(void);

foc_t foc;
foc_cfg_t cfg = {

	.pole_pairs = 14,
	.master_voltage = 12,
	.pwm_period = 2400,// 7200/72 = 100ms
};
struct CurrentDetect Current;
foc_state_e state = Foc_Zero_Angle_Init;
foc_park_t target;

float per = 20;
int main(void)
{
	Serial_Init(115200);
	PWM_Init();
	CurrSense_Init();
	AS5600_Init();
	Systick_CountMode();  //��ʼ����શ�ʱ��

	foc_init(&foc,&cfg);
	TIM2_Init();
	TIM1_Init();

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	RCC_ClocksTypeDef clocks;
//	RCC_GetClocksFreq(&clocks);
	
	while(1)
	{
		Current = GetPhaseCurrent();
		
		if(task_cnt >= TASK_DELAY_MS*5)
		{
			task_cnt = 0;
		}
		else
		{
			continue;
		}
		
		if(state == Foc_Zero_Angle_Init)
		{
			TIM_SetCompare1(TIM2, 2400-100);
			TIM_SetCompare2(TIM2, 0);
			TIM_SetCompare3(TIM2, 0);				

			if(zero_cnt >= ZERO_DELAY_MS)
			{
				zero_cnt = 0;
				foc_zero_angle_updata(&foc);
				state = Foc_Working;

				TIM_SetCompare1(TIM2, 0);
				TIM_SetCompare2(TIM2, 0);
				TIM_SetCompare3(TIM2, 0);
			}
			else
			{
				zero_cnt++;
			}			
		}
		else if(state == Foc_Working)
		{
			
//			if(zero_cnt >= 1000)
//			{			
//				target.d = foc.info.vector_voltage/2;			
//				target.q = 0;
//				foc.park.theta += 1.04719f;
//				zero_cnt = 0;
//			}
//			else
//			{
//				zero_cnt++;
//			}			
			if(per == 0)
			{
				target.d = 0;
				target.q = foc.info.vector_voltage/5;						
			}
			else
			{
				target.d = 0;
				target.q = foc.info.vector_voltage/per;			
			}

		}		
		else if(state == Foc_Shutdown)
		{
			target.d = 0;
			target.q = 0;	
		}
	
		foc_target_updata(&foc,target);
		
	}
}

// TIM1�����жϷ�����
float angle;
void TIM1_UP_IRQHandler(void) {
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
        // �ڴ˴�ִ��5kHz�ж����� 200us
        // ���磺�����߼������ݲɼ���

        task_cnt++;
		
		angle = 1 - GetAngle_NoTrack();
		foc_sensor_updata(&foc,angle);
		
		if(state != Foc_Zero_Angle_Init)
		{
			foc_control(&foc);
			TIM_SetCompare1(TIM2, foc.pwm_duty.a);
			TIM_SetCompare2(TIM2, foc.pwm_duty.b);
			TIM_SetCompare3(TIM2, foc.pwm_duty.c);		
		}
		
        // ����жϱ�־
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

//5khz
void TIM1_Init(void) 
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 1. ʹ��TIM1��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // 3. ����ʱ����Ԫ f = 7200/72Mhz = 100us  x/72 = y ms y*72 = x
    TIM_TimeBaseStructure.TIM_Period = 200*72 - 1;         // �Զ�����ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 0;    // Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    // �߼���ʱ������
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    // 4. ʹ�ܸ����ж�
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    
    // 5. ����NVIC�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  // TIM1�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 6. ������ʱ��
    TIM_Cmd(TIM1, ENABLE);
    
    // 7. ʹ�ܸ߼���ʱ�����������Ҫ���裩
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

//15khz
void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    /*******ѡ����/��ʱ��Դ********/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*********************************/
    
    /*******ѡ���ڲ�ʱ��********/
    TIM_InternalClockConfig(TIM2);
    
    /*******ʱ����Ԫ����********/
	  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;  // ���Ķ���ģʽ1��arrΪ0ʱ����
    TIM_TimeBaseInitStructure.TIM_Period = 2400 - 1;  // ARRֵ (�Զ���װ��ֵ) �����4800 ��0-4800-0,72000000/4800/2 = 7500hz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;  // Ԥ��Ƶ��
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����ccr�ߵ�ƽ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  // ͨ��1 (PA0)
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  // ͨ��2 (PA1)
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);  // ͨ��3 (PA2)
    
    // ����Ԥװ�ؼĴ���
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
    TIM_ARRPreloadConfig(TIM2, ENABLE);  // ����ARRԤװ��
    
    TIM_Cmd(TIM2, ENABLE);
}


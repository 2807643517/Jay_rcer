#include "headfiles.h"


void bsp_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);															 //��ʼ����ʱ����
	
	// ����λ��ͨ��
	can1_CAN1_init();
	
	// ak80
	can2_CAN2_init();
	ak80_control_cmd(AK80_YAW_ID, 0x01);
	ak80_control_cmd(AK80_PITCH_ID, 0x01);
	delay_ms(500);
	ak80_control_cmd(AK80_YAW_ID, 0x03);
	ak80_control_cmd(AK80_PITCH_ID, 0x03);
	delay_ms(500);
	
	// ���׿��� 
	Magnet_GPIOInit();
	
#if (USE_MIT_DRIVER == 0)
	// Ħ���� 
	TIM4_PWM_Init(20000-1, 84-1);
	TIM_SetCompare1(TIM4, 2100);TIM_SetCompare2(TIM4, 2100);
	delay_ms(1000);delay_ms(1000);
	TIM_SetCompare1(TIM4, 900);TIM_SetCompare2(TIM4, 900);
	delay_ms(1000);delay_ms(1000);
#endif
	
	// ���
	TIM3_PWM_Init(20000-1, 84-1);
#if (CUR_ID == 0)
	TIM_SetCompare3(TIM3, 2000);
#else
	TIM_SetCompare3(TIM3, 1050);
#endif
	
	// PS2
	PS2_init();
	
	// ��λ����
	Switch_GPIOInit();
	
#if USE_MIT_DRIVER
	// MIT������
	delay_ms(1500);
	Mit_Driver_Init();
#endif
}

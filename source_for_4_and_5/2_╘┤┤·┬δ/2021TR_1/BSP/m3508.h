#ifndef __M3508_H
#define __M3508_H
#include "stm32f4xx.h"



// M3508���صĵ����ʵ��Ϣ
typedef struct M3508_REAL_INFO
{
	uint16_t ANGLE;   		        //�����Ƕ�						
	int16_t  RPM;								
	int16_t  CURRENT;
	int16_t  TARGET_CURRENT;
	
	// �ǶȻ���ʱ�õ��������
	float		 REAL_ANGLE;         //���������ʵ�Ƕȣ�������float��
	u8			 FIRST_ANGLE_INTEGRAL_FLAG;
	uint16_t LAST_ANGLE;
}M3508_REAL_INFO;


extern struct M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[4];   // 1-4�ֱ��Ӧ˳ʱ�뷽��ĵ��̵��
extern struct M3508_REAL_INFO M3508_CAST_MOTOR_REAL_INFO;
extern struct M3508_REAL_INFO M3508_PITCH_MOTOR_REAL_INFO;
extern struct M3508_REAL_INFO M2006_YAW_MOTOR_REAL_INFO;

extern struct PID M3508_CHASSIS_MOTOR_PID_RPM[4];     // �������
extern struct PID M3508_CAST_MOTOR_PID_RPM;
extern struct PID M3508_PITCH_MOTOR_PID_RPM;
extern struct PID M2006_YAW_MOTOR_PID_RPM;

void M3508_Motor_Init(void);
void m3508_update_m3508_info(CanRxMsg *msg);
void chassis_m3508_send_motor_currents(void);
void shoot_m3508_send_motor_currents(void);
void M3508AngleIntegral(M3508_REAL_INFO *M3508_MOTOR);

#endif





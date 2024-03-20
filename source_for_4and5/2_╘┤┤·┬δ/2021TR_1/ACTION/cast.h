#ifndef __CAST_H
#define __CAST_H

#include "stm32f4xx.h"

#define CAST_V_MAX	1.5f
#define CAST_V_MIN	0.3f
#define CAST_ACC		0.01f

typedef struct MOTOR_VELOCITY_PLANNING
{
	float Pstart;        //��ʼλ��
	float Pend;          //����λ��
	float Vstart;        //��ʼ���ٶ�           // ��λ��RPM ����ֵ
	float Vmax;          //�����ٶ�
	float Vend;          //ĩβ���ٶ�
	float Rac;           //����·�̵ı���
	float Rde;           //����·�̵ı���
}MOTOR_VELOCITY_PLANNING;


int MotorRPMPlan(MOTOR_VELOCITY_PLANNING motion, float pos, int16_t *motor_target_rpm);

extern float CAST_MOTOR_TARGET_RPM;

extern int TopSwitch_State;
extern float cast_target_v;

#endif

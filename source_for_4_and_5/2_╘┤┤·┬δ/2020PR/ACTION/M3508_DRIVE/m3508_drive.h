#ifndef __M3508_DRIVE_H
#define __M3508_DRIVE_H
#include "stm32f4xx.h"

#define TURNPLATE_INIT_POS            0     // ת�̳�ʼλ��
#define TURNPLATE_1st_SHOOT_POS    -32.5    // ת�����һ����λ��//32.5
#define TURNPLATE_2nd_SHOOT_POS    -41.5    // ת����ڶ�����λ��
#define TURNPLATE_3rd_SHOOT_POS    -50.4    // ת�����������λ��
#define TURNPLATE_4th_SHOOT_POS    -37.2    // ת������ĸ���λ��
#define TURNPLATE_5th_SHOOT_POS    -32.1    // ת����������λ��

//#define TURNPLATE_INIT_POS            0     // ת�̳�ʼλ��
//#define TURNPLATE_1st_SHOOT_POS    -29.8    // ת�����һ����λ��
//#define TURNPLATE_2nd_SHOOT_POS    -48.5    // ת����ڶ�����λ��
//#define TURNPLATE_3rd_SHOOT_POS    -55.5    // ת�����������λ��
//#define TURNPLATE_4th_SHOOT_POS    -37.0    // ת������ĸ���λ��
//#define TURNPLATE_5th_SHOOT_POS    -28.3    // ת����������λ��

#define ARM_INIT_POS                  0    // �����е�۵ĳ�ʼλ��
#define ARM_SHOOT_POS              -90    // ���¼���Ҫ�󵽴��λ��

	


typedef struct ARM_VELOCITY_PLANNING //����������ٶȹ滮
{
	float Pstart;        //��ʼλ��
	float Pend;          //����λ��
	float Vstart;        //��ʼ���ٶ�           // ��λ��RPM ����ֵ
	float Vmax;          //�����ٶ�
	float Vend;          //ĩβ���ٶ�
	float Rac;           //����·�̵ı���
	float Rde;           //����·�̵ı���
}ARM_VELOCITY_PLANNING;

typedef struct TURNPLATE_VELOCITY_PLANNING  //����ת�̻������ٶȹ滮
{
	float Pstart;        //��ʼλ��
	float Pend;          //����λ��
	float Vstart;        //��ʼ���ٶ�           // ��λ��RPM ����ֵ
	float Vmax;          //�����ٶ�
	float Vend;          //ĩβ���ٶ�
	float Rac;           //����·�̵ı���
	float Rde;           //����·�̵ı���
}TURNPLATE_VELOCITY_PLANNING;

extern struct ARM_VELOCITY_PLANNING *ARM_NOW_MOTION; 
extern struct ARM_VELOCITY_PLANNING ARM_HOLD_MOTION;  
extern struct ARM_VELOCITY_PLANNING ARM_RESET_MOTION;
extern struct ARM_VELOCITY_PLANNING ARM_SHOOT_MOTION;
extern struct ARM_VELOCITY_PLANNING ARM_SHOOT_MOTION2;
extern struct ARM_VELOCITY_PLANNING ARM_SHOOT_2_MOTION;



void Motor_motion_control(void *pdata);                                                     //�����������
void M3508_arm_motor_motion_control(void);                                                  //��е�ۻ����������
void M2006_turnplate_motion_control(void);                                                  //ת�̶�������

void ad_plan_arm_motor_RPM(ARM_VELOCITY_PLANNING motion, float pos);                        //��е�ۻ����ٶȹ滮



#endif

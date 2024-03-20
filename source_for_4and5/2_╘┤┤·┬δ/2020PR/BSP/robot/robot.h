#ifndef __ROBOT_H
#define __ROBOT_H

#include "stm32f4xx.h"

#define RESET_DELAY_10MS 100  // ҡ������ʱ����ʱ����
#define RESET_PULL_DELAY_10MS 1000  // ҡ������ʱ����ʱ����
#define PREPARE_DELAY_1S 100

//����״̬����ö�����ͱ���
typedef enum
{
	
  ROBOT_INIT,                                         //��ʼ��
	ROMOTE_RESTART,                                     //����״̬
	ROMOTE_PREPARATION,                                 //׼��״̬
	ROMOTE_START,                                       //ң�ؿ�ʼ
	
	START_TO_BALL_1st,                                  //��������ǰ����һ������� 
	THROW_1st_BALL,                                   	//����һ��1����
	
	TO_BALL_2nd,                                        //ǰ���ڶ��������
	THROW_2nd_BALL,                                     //���ڶ���1����
  
	TO_BALL_3rd,                                        //ǰ�������������
	THROW_3rd_BALL,                                     //������1����
	
	TO_BALL_4th,                                        //ǰ�����ĸ������
	THROW_4th_BALL,                                     //�����ĸ�1����
	
	THROW_5th_BALL,                                     //�������1����
	
	RESTART_TO_2,                                       //�������ڶ�����
	RESTART_TO_3,                                       //��������������
	RESTART_TO_4,                                       //���������ĸ���
	
	TO_START,                                           //�ӵ���������ǰ��������
	
	START_TO_1st_KICK,                                  //��������ǰ��2����������
	KICK_1st,                                           //��2��������
	
	KICK_1st_TO_START,                                  //��2����������ǰ��������
	
	START_TO_2nd_KICK,                                  //��������ǰ��3����������
	
  KICK_2nd,                                           //��3��������
	
  TO_BALL_5th,                                        //�������ǰ������������
	
  BALL_5th_TO_START,                                

  RESTART_TO_START,

	
}NOWStatus_t;

typedef enum
{
	THROW_STOP,
	THROW_START,
	THROW_SUCCEEDED,
	THROW_RESET,
	THROW_RESET_SUCCEEDED,
	
}shootStatus_t;

typedef enum
{
	STOP,
	MOVING,
	ARRIVE,
}moveStatus_t;

typedef enum
{
	TURN_STOP,
	TURN_SUCCEED,
}turnplateStatus_t;

typedef enum
{
	KICK_STOP,
	KICK_START1,
	KICK_START2,
	KICK_START3,
	KICK_END1,
	KICK_END2,
	KICK_END3,
	KICK_SUCCEED,
	STOP_2P,
	STOP_START_2P,
	STOP_3P,
	STOP_START_3P,
	GO_2P,
	BACK_2P,
	GO_3P,
	BACK_3P,
	GO_5_ball,
	STOP_5_ball,
}kickStatus_t;

typedef enum
{
	ok_put,
  no_put,
	
}put_liyu;

typedef enum
{
	ok_kick,
  no_kick,
	
	
}kick_safe;//���򱣻�


//ȫ�ֱ����ṹ��
typedef struct{
	NOWStatus_t   NOW_STATE;
	moveStatus_t  MOVE_STATE;
	shootStatus_t SHOOTSTATE;
	turnplateStatus_t TURNSTATE;
	kickStatus_t KICK_STATE;
	put_liyu PUT_LIYU;
	kick_safe KICK_SAFE;
}ROBOT_STATE_ITEMS;


extern float INIT_POS;
extern float INIT_X;
extern float INIT_Y;
extern ROBOT_STATE_ITEMS ROBOT;	

void FSM_RUN(void *pdata);
#endif

#include "includes.h"


float CUR_POS[3] = {0, 0, 0};	// ��ǰλ��x,y,yaw
// �ƶ�״̬��
void Move_task(void *pvParameters)
{
	// ������ʱ
	static portTickType move_xLastWakeTime;
	const portTickType move_xFrequency = pdMS_TO_TICKS(10); // ��ʱ10ms
	move_xLastWakeTime = xTaskGetTickCount(); // ��ȡ��ǰ����ֵ
	
	float move_time_counter = 0;
	
	while(1)
	{
		switch(MOVE_STATE)
		{
			// ֹͣ
			case MOVE_STOP:
//				LockupPoint(CUR_POS[0], CUR_POS[1], CUR_POS[2]);
				break;
			
			// �ƶ���1��Ͷ����
			case MOVE_2_CAST_POINT_1:
				move_time_counter += 0.01f;
				if(PathPlan(move_time_counter, 4.0, 5+1, X1, Y1, Yaw1))
				{
					ROBOT_STATE = ROBOT_STATE_RELOAD;
					move_time_counter = 0;
					MOVE_STATE = MOVE_STOP;
					CAST_STATE = CAST_STATE_TOP;
				}
				break;
			
//			// �ƶ���2��Ͷ����-3.8
//			case MOVE_2_CAST_POINT_2:
//				time_counter += 0.01f;
//				if(PathPlan(time_counter, 3.8, 5+1, X, Y, Yaw))
//				{
//					CUR_POS[0] = X[5+3];
//					CUR_POS[1] = Y[5+3];
//					CUR_POS[2] = Yaw[5+3];
//					time_counter = 0;
//					MOVE_STATE = MOVE_STOP;
//				}
//				break;
				
			// �ƶ���ȡ����
			case MOVE_2_LOAD_ARROW:
				move_time_counter += 0.01f;
				if(PathPlan(move_time_counter, 7.5, 5+1, X, Y, Yaw))
				{
					ROBOT_STATE = ROBOT_STATE_RELOAD;
					move_time_counter = 0;
					MOVE_STATE = MOVE_STOP;
				}
				break;
						
			default:
				break;
		}
		
		vTaskDelayUntil(&move_xLastWakeTime, move_xFrequency); // ������ʱ
	}
}


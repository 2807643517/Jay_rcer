#include "includes.h"


//ChassisDrive任务
void ChassisDrive_task(void *pvParameters)
{	
	while(1)
	{		
		// 速度分解
		World_3wheels(ROBOT_TARGET_VELOCITY_DATA.Vx_RPM,
									ROBOT_TARGET_VELOCITY_DATA.Vy_RPM, 
									ROBOT_TARGET_VELOCITY_DATA.W_RPM,
									ROBOT_REAL_POS_DATA.POS_YAW);
		
		// 进行PID计算
		PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[0], M3508_CHASSIS_MOTOR_REAL_INFO[0].RPM, CHASSIS_MOTOR_TARGET_RPM.MOTOR1_RPM);
		PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[1], M3508_CHASSIS_MOTOR_REAL_INFO[1].RPM, CHASSIS_MOTOR_TARGET_RPM.MOTOR2_RPM);
		PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[2], M3508_CHASSIS_MOTOR_REAL_INFO[2].RPM, CHASSIS_MOTOR_TARGET_RPM.MOTOR3_RPM);
//		PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[3], M3508_CHASSIS_MOTOR_REAL_INFO[3].RPM, CHASSIS_MOTOR_TARGET_RPM.MOTOR4_RPM);
		
		// 设置电流
		M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[0].output;
		M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[1].output;
		M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[2].output;
//		M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[3].output;
		
		// 发送数据
		chassis_m3508_send_motor_currents();
		
		vTaskDelay(5);
	}
}


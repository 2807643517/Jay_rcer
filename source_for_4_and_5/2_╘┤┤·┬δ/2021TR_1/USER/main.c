#include "includes.h"

TaskHandle_t RunTimeStats_Handler;
TaskHandle_t ChassisDrive_Handler;
TaskHandle_t DataScope_Handler;
TaskHandle_t Debug_Handler;
TaskHandle_t Cast_Handler;
TaskHandle_t Move_Handler;
TaskHandle_t Take_Handler;
TaskHandle_t FSM_Handler;

int start_flag = 0;


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// ����ϵͳ�ж����ȼ�����4
	delay_init(168);															 	// ��ʼ����ʱ����
	
	USART6_init(9600);	// ���������
		
	CAN1_Init();																		// CAN1
	M3508_Motor_Init();															// M3508���
	delay_ms(500);
	ak80_control_cmd(AK80_MOTOR_ID, 0x01);delay_ms(500);			// ȡ������AK80���
	ak80_control_cmd(AK80_MOTOR_ID, 0x03);delay_ms(500);
	AK80_motion_control(AK80_MOTOR_ID, 0, 0, 45, 5, 0);
	
	can2_CAN2_init();
	
	Location_Init();			// ��λ
	MoveInit();						// �ƶ�
	
	Cylinder_GPIOInit();
	Switch_GPIOInit();
	
	PS2_init();						// PS2
	
	while(!start_flag) delay_ms(10);

	ROBOT_STATE = ROBOT_STATE_INIT;
	
	taskENTER_CRITICAL();           //�����ٽ���
	
#if USE_DATASCOPE
	//DataScope����
	xTaskCreate((TaskFunction_t )DataScope_task,     
							(const char*    )"DataScope_task",   
							(uint16_t       )DATASCOPE_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )DATASCOPE_TASK_PRIO,
							(TaskHandle_t*  )&DataScope_Handler);
#endif
#if USE_DEBUG
	//Debug����
	xTaskCreate((TaskFunction_t )Debug_task,     
							(const char*    )"Debug_task",   
							(uint16_t       )DEBUG_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )DEBUG_TASK_PRIO,
							(TaskHandle_t*  )&Debug_Handler);
#endif
	//ChassisDrive����
	xTaskCreate((TaskFunction_t )ChassisDrive_task,     
							(const char*    )"ChassisDrive_task",   
							(uint16_t       )CHASSIS_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )CHASSIS_TASK_PRIO,
							(TaskHandle_t*  )&ChassisDrive_Handler);
	//Cast����
	xTaskCreate((TaskFunction_t )Cast_task,     
							(const char*    )"Cast_task",   
							(uint16_t       )CAST_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )CAST_TASK_PRIO,
							(TaskHandle_t*  )&Cast_Handler);
#if USE_PATH
	//Move����
	xTaskCreate((TaskFunction_t )Move_task,     
							(const char*    )"Move_task",   
							(uint16_t       )MOVE_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )MOVE_TASK_PRIO,
							(TaskHandle_t*  )&Move_Handler);
#endif
	//Take����
	xTaskCreate((TaskFunction_t )Take_task,     
							(const char*    )"Take_task",   
							(uint16_t       )TAKE_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )TAKE_TASK_PRIO,
							(TaskHandle_t*  )&Take_Handler);
	//FSM����
	xTaskCreate((TaskFunction_t )FSM_task,     
							(const char*    )"FSM_task",   
							(uint16_t       )FSM_STK_SIZE,
							(void*          )NULL,
							(UBaseType_t    )FSM_TASK_PRIO,
							(TaskHandle_t*  )&FSM_Handler);

	taskEXIT_CRITICAL();            //�˳��ٽ���
	              
	vTaskStartScheduler();          //�����������
}


#include "includes.h"


#if USE_DATASCOPE
//DataScope����
void DataScope_task(void *pvParameters)
{
	unsigned char i;          //��������
	unsigned char Send_Count; //������Ҫ���͵����ݸ���
	
	while(1)
	{
		DataScope_Get_Channel_Data(M3508_SHOOT_MOTOR_REAL_INFO[0].REAL_ANGLE, 1);
		Send_Count = DataScope_Data_Generate(1);
		for( i = 0 ; i < Send_Count; i++) 
		{
			while((USART1->SR&0X40)==0);  
			USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
		vTaskDelay(10);
	}
}
#endif



#if USE_DEBUG
//Debug����
void Debug_task(void *pvParameters)
{		
	
}
#endif

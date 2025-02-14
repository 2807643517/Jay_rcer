#include "headfiles.h"


// CAN1初始化 用于ROBOMODULE
// PA11 -> CANRX
// PA12 -> CANTX
void can1_CAN1_init(void)
{
	CAN_InitTypeDef        can; 
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef       gpio;
	NVIC_InitTypeDef       nvic;

	// 开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	// 配置所用IO口
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

	gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio);
	
	// 配置CAN的工作模式
	CAN_DeInit(CAN1);
	CAN_StructInit(&can);
	
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TXFP = ENABLE;
	can.CAN_Mode = CAN_Mode_Normal;
	can.CAN_SJW  = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_9tq;
	can.CAN_BS2 = CAN_BS2_4tq;
	can.CAN_Prescaler = 3;   //设置CAN波特率为 42/(1+9+4)/3=1Mbps
	CAN_Init(CAN1, &can);

	// 配置筛选器
	can_filter.CAN_FilterNumber = 0;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh = 0x0000;
	can_filter.CAN_FilterIdLow = 0x0000;
	can_filter.CAN_FilterMaskIdHigh = 0x0000;
	can_filter.CAN_FilterMaskIdLow = 0x0000;
	can_filter.CAN_FilterFIFOAssignment = 0;
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
	
	// 配置中断控制器
	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	nvic.NVIC_IRQChannel = CAN1_TX_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	// 使能CAN中断
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);  // FIFO0接收中断
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);  // 发送中断
}


// CAN1的发送中断函数
void CAN1_TX_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
		{
	   CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
			
    }
}


/*WAITING_TEST*/
// CAN1的FIFO0接受中断函数
void CAN1_RX0_IRQHandler(void)
{
  CanRxMsg CAN1_RX0_message;  // 临时存放接受数据的结构体
	
  if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
  {
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1_RX0_message);  // 读取数据
		
		Upper_update_info(&CAN1_RX0_message);
	
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
  }
}


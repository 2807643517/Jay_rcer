#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define Max_BUFF_Len 				18	  

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         				//����״̬���	

extern u8 Uart6_Buffer[Max_BUFF_Len];
extern u8 RES_2;

typedef struct ENCODER
{
	int angle_data1;
	int angle_data2;
	int angle_data3;	
	int angle_data4;	
	
	int check_data1;
	int check_data2;
	float angle;

}ENCODER;

#define ABSOLUTE_ENCODER 1024.0f
#define REDUCTION 18/66

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void USART2_Init(uint32_t BaudRate);
void UART5_Init(uint32_t BaudRate);
void Action_Uart_init(u32 baud_rate);
void USART6_init(u32 bound);
void Usart6_Send_Order(u8 order);
#endif



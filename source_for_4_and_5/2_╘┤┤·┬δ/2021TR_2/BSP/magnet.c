#include "headfiles.h"


// ������ʼ��
void Magnet_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;		
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // ��ʱ��

	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // ��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}


void Throw_Enable(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}
void Throw_Disable(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

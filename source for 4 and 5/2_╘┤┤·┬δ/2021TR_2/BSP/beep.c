#include "headfiles.h"


// ����������GPIO��ʼ��
// BEEP -> PF2
void Beep_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;		
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  // ��ʱ��

	//��ʼ����Ӧ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // ��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	// �ȹرշ�����
	GPIO_ResetBits(GPIOF, GPIO_Pin_2);
}



//������ָʾ��1s
void Beep_ON_OFF(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_2);
	vTaskDelay(1000);
	GPIO_ResetBits(GPIOF, GPIO_Pin_2);
	vTaskDelay(1000);
}

#include "includes.h"


// ��ʵλ������
ROBOT_REAL_POS ROBOT_REAL_POS_DATA = {0, 0, 0};

// ƫ����λ��ƫ����
float OFFSET_YAW = 0;


// ȫ����λ��ʼ��
void Location_Init(void)
{ 
	Action_Uart_init(115200);
}


extern int start_flag;
// �ڴ���3�ж���ʹ��
void USART3_IRQHandler(void)
{
	static uint8_t ch;
	static union
	{
	 uint8_t data[24];
	 float ActVal[6];
	}posture;
	
	static uint8_t count = 0;
  static uint8_t i = 0;
	
	start_flag = 1;

	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)   
	{
		ch = USART_ReceiveData(USART3);

		switch(count)
		{
			case 0:
			{
				if(ch == 0x0d) count ++;
				else count = 0;
			}
			break;
				 
			case 1:
			{
				if(ch == 0x0a)
				{
					i = 0;
					count ++;
				}
				else if(ch == 0x0d);
				else count = 0;
			}
			break;
				 
			case 2:
			{
			 posture.data[i] = ch;
			 i ++;
			 if(i >= 24)
			 {
				 i = 0;
				 count ++;
			 }
			}
			break;
				 
			case 3:
			{
				if(ch == 0x0a) count++;
				else
				count = 0;
			}
			break;
				 
			case 4:
			{
				if(ch == 0x0d)
				{					 
					//���´���������					 
					Update_Action_gl_position(posture.ActVal);
				}
			  count = 0;
			}
			break;
			 
			default:
			{
				count = 0;
			}
			break;		 
		}
		 
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
	}
}


// actionȫ����λģ�鶨λ����
ACTION_GL_POS ACTION_GL_POS_DATA = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// ����actionȫ����λģ���ֵ
void Update_Action_gl_position(float value[6])
{
	// ��¼��ε�ֵ
	ACTION_GL_POS_DATA.ANGLE_Z = value[0];  // ����
	ACTION_GL_POS_DATA.ANGLE_X = value[1];
	ACTION_GL_POS_DATA.ANGLE_Y = value[2];
	ACTION_GL_POS_DATA.POS_X   = value[3];  // ����
	ACTION_GL_POS_DATA.POS_Y   = value[4];  // ����
	ACTION_GL_POS_DATA.W_Z     = value[5];

	// ƫ����ֱ�Ӹ�ֵ����ʱ��Ϊ����˳ʱ��Ϊ����
  ROBOT_REAL_POS_DATA.POS_YAW = ACTION_GL_POS_DATA.ANGLE_Z - OFFSET_YAW;
	
	//������е���,��ֵX��Y
	ROBOT_REAL_POS_DATA.POS_X = ACTION_GL_POS_DATA.POS_X + INSTALL_ERROR_Y * sin(ROBOT_REAL_POS_DATA.POS_YAW * PI / 180.0f);
	ROBOT_REAL_POS_DATA.POS_Y = ACTION_GL_POS_DATA.POS_Y - INSTALL_ERROR_Y * (cos(ROBOT_REAL_POS_DATA.POS_YAW * PI / 180.0f)-1);
}


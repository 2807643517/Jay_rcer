#include "includes.h"


float CAST_MOTOR_TARGET_RPM = 0 ;    // ̧�����Ŀ���ٶ�


// �������
MOTOR_VELOCITY_PLANNING cast_motor_motion_0m = {0,    3.0, 100, 2800, 100, 0.3, 0.3};				// ��λ
MOTOR_VELOCITY_PLANNING cast_motor_motion_4m = {0, -440.0, 600, 2300, 100, 0.2, 0.2};				// ��4m (end = -470.0
MOTOR_VELOCITY_PLANNING cast_motor_motion_6m = {-440.0, -550.0, 600,  1500, 100, 0.3, 0.3};	// ��6m



// ���RPM�滮
int motor_plan_first_time_flag = 1;
int MotorRPMPlan(MOTOR_VELOCITY_PLANNING motion, float pos, int16_t *motor_target_rpm)
{
	static float Ssu;   //��·��
	static float Sac;   //����·��
	static float Sde;   //����·��
	static float Sco;   //����·��
	static float Aac;   //���ټ��ٶ�
	static float Ade;   //���ټ��ٶ�
	static float S;     //��ǰ·��
	
	//����Ŀ���
	if(motion.Pend < motion.Pstart && pos < motion.Pend)
	{
		motor_plan_first_time_flag = 1;
		return 1;
	}
	else if(motion.Pend > motion.Pstart && pos > motion.Pend)
	{
		motor_plan_first_time_flag = 1;
		return 1;
	}
	
	// �����������������ִ���ٶȹ滮
	if((motion.Rac > 1) || (motion.Rac < 0) ||
		 (motion.Rde > 1) || (motion.Rde < 0) ||
		 (motion.Vmax < motion.Vstart) )
	{
		*motor_target_rpm = 0;  // ��������
		return -1;
	}
	
	// ����ģʽ
	if(motion.Pstart == motion.Pend)
	{
		*motor_target_rpm = motion.Vstart * motion.Vmax;
		return 0;
	}
	
	// ��һ�ε��ã�����һЩ����
	if(motor_plan_first_time_flag)
	{
		motor_plan_first_time_flag = 0;
		Ssu = ABS(motion.Pend - motion.Pstart);    
		Sac = Ssu * motion.Rac;
		Sde = Ssu * motion.Rde;
		Sco = Ssu - Sac - Sde;
		Aac = (motion.Vmax * motion.Vmax - motion.Vstart * motion.Vstart) / (2.0f * Sac);
		Ade = (motion.Vend * motion.Vend -   motion.Vmax *   motion.Vmax) / (2.0f * Sde);
	}
	
	// �����쳣���
	if(((motion.Pend > motion.Pstart) && (pos < motion.Pstart)) ||
		 ((motion.Pend < motion.Pstart) && (pos > motion.Pstart)))
	{
		*motor_target_rpm = motion.Vstart;
	}
	else if(((motion.Pend > motion.Pstart) && (pos > motion.Pend)) ||
		      ((motion.Pend < motion.Pstart) && (pos < motion.Pend)))
	{
		*motor_target_rpm = motion.Vend;
	}
	else
	{
		S = ABS(pos - motion.Pstart);
		
		// �滮RPM
		if     (S < Sac)       *motor_target_rpm = sqrt(2.0f * Aac * S + motion.Vstart * motion.Vstart);         // ���ٽ׶�
		else if(S < (Sac+Sco)) *motor_target_rpm = motion.Vmax;                                                  // ���ٽ׶�
		else                   *motor_target_rpm = sqrt(motion.Vend * motion.Vend - 2.0f * Ade * ABS(Ssu - S));  // ���ٽ׶�
	}
	
	// ������ʵ�������
	if(motion.Pend < motion.Pstart) *motor_target_rpm = -*motor_target_rpm;
	return 0;
}






#ifndef _CONTROL_H
#define _CONTROL_H

#include "sys.h"

struct PID                           //�ṹ��
	{
	int Set;				//�趨ֵ
	int Actual;			//ʵ��ֵ
	int err;				//��ǰ���
	int err_last;		//��һ�����
	
	float Kp,Ki,Kd,Kout;
	int voltage;			//����ֵ
	int integral;		//������ֵ
};
int PID_realize(void);
void PID_Init(void);
void Load(int PWM);
int GFP_abs(int p);
#endif

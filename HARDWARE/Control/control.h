#ifndef _CONTROL_H
#define _CONTROL_H

#include "sys.h"

struct PID                           //结构体
	{
	int Set;				//设定值
	int Actual;			//实际值
	int err;				//当前误差
	int err_last;		//上一次误差
	
	float Kp,Ki,Kd,Kout;
	int voltage;			//计算值
	int integral;		//误差积分值
};
int PID_realize(void);
void PID_Init(void);
void Load(int PWM);
int GFP_abs(int p);
#endif

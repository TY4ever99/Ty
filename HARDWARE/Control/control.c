#include "control.h"
#include "sport.h"
#include "oled.h"
#include "delay.h"

extern int ANGLE;						
extern int SETANGLE;


struct PID pid;

void PID_Init(void)					//因为有储存，因此用ReadPID()代替
{
	
	pid.Set=SETANGLE;
	pid.Actual=ANGLE;
	pid.err=0;
	pid.err_last=0;                                                                                                                                                                                                   

	pid.Kp=50;						//实际为除1倍
	pid.Ki=0.005;						//实际为除1倍
	pid.Kd=-800;						//实际为除1倍
	pid.Kout=0;						//偏移值
	pid.voltage=0;
	pid.integral=0;
}

int PID_realize(void)
{
	int t;
	pid.Set      = SETANGLE;					//设定值 700
	pid.Actual   = ANGLE;					//实际值 100-700
	pid.err      = pid.Set - pid.Actual;	//之差
	

	pid.integral = pid.integral + pid.err;      //累计误差和


	pid.voltage = pid.Kp*pid.err								//设定值与实际的偏差
				+ pid.Ki*pid.integral					//历史累计偏差
				+ pid.Kd*(pid.err-pid.err_last)					//本次偏差与上次偏差比较
				+ pid.Kout;										//最终计算值
	    //delay_ms(1000);
	pid.err_last = pid.err;
	
	t=pid.voltage;
	//OLED_ShowNum(0,0,SETANGLE,4,16);
	//OLED_ShowNum(0,2,ANGLE,4,16);
	//OLED_ShowNum(50,4,pid.Set,4,16);
	//OLED_ShowNum(50,6,pid.Actual,4,16);
	if(t>3599)		t=7199;
	else if(t<-3599)	t=-7199; //限幅

	return t;
}

/*绝对值函数*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

void Load(int PWM)
{
	//1.研究正负号，对应正反转
	if(PWM>=0)	zhuanquan(GFP_abs(PWM));//正转
	else 				fanzhuan(GFP_abs(PWM));//反转
}


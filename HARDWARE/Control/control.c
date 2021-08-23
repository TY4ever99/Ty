#include "control.h"
#include "sport.h"
#include "oled.h"
#include "delay.h"

extern int ANGLE;						
extern int SETANGLE;


struct PID pid;

void PID_Init(void)					//��Ϊ�д��棬�����ReadPID()����
{
	
	pid.Set=SETANGLE;
	pid.Actual=ANGLE;
	pid.err=0;
	pid.err_last=0;                                                                                                                                                                                                   

	pid.Kp=50;						//ʵ��Ϊ��1��
	pid.Ki=0.005;						//ʵ��Ϊ��1��
	pid.Kd=-800;						//ʵ��Ϊ��1��
	pid.Kout=0;						//ƫ��ֵ
	pid.voltage=0;
	pid.integral=0;
}

int PID_realize(void)
{
	int t;
	pid.Set      = SETANGLE;					//�趨ֵ 700
	pid.Actual   = ANGLE;					//ʵ��ֵ 100-700
	pid.err      = pid.Set - pid.Actual;	//֮��
	

	pid.integral = pid.integral + pid.err;      //�ۼ�����


	pid.voltage = pid.Kp*pid.err								//�趨ֵ��ʵ�ʵ�ƫ��
				+ pid.Ki*pid.integral					//��ʷ�ۼ�ƫ��
				+ pid.Kd*(pid.err-pid.err_last)					//����ƫ�����ϴ�ƫ��Ƚ�
				+ pid.Kout;										//���ռ���ֵ
	    //delay_ms(1000);
	pid.err_last = pid.err;
	
	t=pid.voltage;
	//OLED_ShowNum(0,0,SETANGLE,4,16);
	//OLED_ShowNum(0,2,ANGLE,4,16);
	//OLED_ShowNum(50,4,pid.Set,4,16);
	//OLED_ShowNum(50,6,pid.Actual,4,16);
	if(t>3599)		t=7199;
	else if(t<-3599)	t=-7199; //�޷�

	return t;
}

/*����ֵ����*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

void Load(int PWM)
{
	//1.�о������ţ���Ӧ����ת
	if(PWM>=0)	zhuanquan(GFP_abs(PWM));//��ת
	else 				fanzhuan(GFP_abs(PWM));//��ת
}


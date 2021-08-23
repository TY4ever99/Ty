#include "delay.h"
#include "sys.h"
#include "adc.h"
#include "pwm.h"
#include "shineng.h"
#include "usart.h"
#include "bmp.h"
#include "oled.h"
#include "sport.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "usmart.h"
#include "control.h"
#include "exti.h"

float Pitch,Roll,Yaw;
int ANGLE;						
int SETANGLE;

void GET_ANGLE(void);

 int main(void)
 {	 
	delay_init();	    	 //延时函数初始化	
 	 
 	NVIC_Configuration();
	OLED_Init();
	TIM2_PWM_Init(7199,0);
	TIM2_PWM_Init1(7199,0);
	TIM3_Int_Init(1000-1,7200-1);
	shineng_Init();
	Adc_Init();	  		//ADC初始化
  uart_init(500000);	 	//串口初始化为500000
	usmart_dev.init(72);		//初始化USMART
	MPU_Init();
	OLED_Clear();
	PID_Init();
	 
	SETANGLE=90;
	 
 	 while(mpu_dmp_init())
 	{
		
	}  
	
	while(1)
	{
	GET_ANGLE();
	} 
}	

void GET_ANGLE(void)
{
   mpu_dmp_get_data(&Pitch,&Roll,&Yaw);
   ANGLE=Yaw;
	 OLED_ShowNum(50,2,ANGLE,4,16);
	 OLED_ShowNum(50,0,GFP_abs(PID_realize()),4,16);
}

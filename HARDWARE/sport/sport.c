#include "sport.h"
#include "delay.h"
#include "adc.h"

void xiangqian()
{
   TIM_SetCompare2(TIM2,850);
   TIM_SetCompare1(TIM2,1000);
   GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	 GPIO_SetBits(GPIOB,GPIO_Pin_13);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_14);
   GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void zhuanquan(int t)
{
	TIM_SetCompare2(TIM2,t);
  TIM_SetCompare1(TIM2,t);
  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
  GPIO_SetBits(GPIOB,GPIO_Pin_14);
}

void fanzhuan(int t)
{
	TIM_SetCompare2(TIM2,t);
  TIM_SetCompare1(TIM2,t);
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
  GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void tingzhi()
{
  TIM_SetCompare2(TIM2,3599);
  TIM_SetCompare1(TIM2,3599);
}

u8 cezhang()
{
  u16 adcx;
  u16 xiaoshu;
	float temp;
  adcx=Get_Adc_Average(ADC_Channel_2,10);
	temp=(float)adcx*(3.3/4096);
	adcx=temp;
	temp-=adcx;
	xiaoshu=temp*100;
	if (adcx==0&&xiaoshu<90) 
		return 0;         //ÎÞÕÏ°­
	else 
		return 1;         //ÓÐÕÏ°­
}

#include "exti.h"
#include "sys.h" 
#include "control.h"

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period		=	arr;	//��ʼ����ʱ��3
	TIM_TimeBaseInitStructure.TIM_Prescaler		=	psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	=	TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);				//����ʱ��3�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel 						=	TIM3_IRQn;	//��ʼ��NVIC
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			=	0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					=	ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE);									//ʹ�ܶ�ʱ��3
}
void TIM3_IRQHandler(void)
{
	Load(PID_realize());
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

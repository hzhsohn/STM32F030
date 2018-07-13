/*
  2018/7/9
  Copyright (C) Han.zhihong
	
	
����:
	
	zhSCM_GPIOConfig(GPIOA, GPIO_Pin_3); 
	zhSCM_GPIOConfig(GPIOA, GPIO_Pin_4); 
	
	EzhKeyEvent ev;
  EzhKeyState GPIOAStatus1;//һ��GPIO��Ӧһ��EzhKeyState����
	EzhKeyState GPIOAStatus2;
  zhSCM_initKeyState(&GPIOAStatus1);
	zhSCM_initKeyState(&GPIOAStatus2);
  //ѭ��--------------- BEGIN---------
	while(1)
	{
		//����1
		ev=zhSCM_keyState(&GPIOAStatus1,GPIOA,GPIO_Pin_3);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
				break;
      case ZH_KEY_EVENT_PRESS:
				break;
      case ZH_KEY_EVENT_UP:
        break;
    }
		//����2
		ev=zhSCM_keyState(&GPIOAStatus2,GPIOA,GPIO_Pin_4);
    switch(ev)
    {
			case ZH_KEY_EVENT_NONE:
				break;
      case ZH_KEY_EVENT_DOWN:
        break;
      case ZH_KEY_EVENT_PRESS:
        break;
      case ZH_KEY_EVENT_UP:
        break;
    }
	}
  //ѭ��--------------- END---------
	
*/

#ifndef __KEY_H
#define __KEY_H


#include "delay.h"

#define KEY_AHBP 	RCC_AHBPeriph_GPIOA


/*******************************************************************************
* ����         : ����
* ����          : �������õ�״̬���¼���ʶ
*******************************************************************************/
typedef enum _EzhKeyState{
   ZH_KEY_STATE_0,
   ZH_KEY_STATE_1,
   ZH_KEY_STATE_2,
   ZH_KEY_STATE_3,
}EzhKeyState;
typedef enum _EzhKeyEvent{
   ZH_KEY_EVENT_NONE,
   ZH_KEY_EVENT_DOWN,
   ZH_KEY_EVENT_PRESS,
   ZH_KEY_EVENT_UP
}EzhKeyEvent;


void zhSCM_GPIOConfig(GPIO_TypeDef* GPIOx,u16 Pin_x);
void zhSCM_initKeyState(EzhKeyState *status);
EzhKeyEvent zhSCM_keyState(EzhKeyState *status,GPIO_TypeDef *GPIOx,u16 GPIO_Pin_x);

#endif


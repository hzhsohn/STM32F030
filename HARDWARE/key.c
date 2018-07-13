/*
  2018/7/9
  Copyright (C) Han.zhihong
*/


#include "key.h"

/*******************************************************************************
* ������       : zhSCM_GPIOConfig
* ��������      : ���ø�GPIO�˿ڹ���
* �������      : �Լ���
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
void zhSCM_GPIOConfig(GPIO_TypeDef* GPIOx,u16 Pin_x)
{
  GPIO_InitTypeDef GPIO_InitStructure={0};
	
	RCC_AHBPeriphClockCmd(KEY_AHBP, ENABLE);  //ʹ��GPIOA��ʱ��
	
  GPIO_InitStructure.GPIO_Pin = Pin_x;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
/*******************************************************************************
* ������       : zhSCM_initKeyState
* ��������      : ��ʼ��GPIO����״̬
* �������      : EzhKeyState�ı���
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
void zhSCM_initKeyState(EzhKeyState *status)
{
  *status=ZH_KEY_STATE_0;
}
/*******************************************************************************
* ������       : zhSCM_keyState
* ��������      : ����GPIO�˿ڰ�������
* �������      : ������
* ������      : ��
* ����ֵ        : ��
*******************************************************************************/
EzhKeyEvent zhSCM_keyState(EzhKeyState *status,GPIO_TypeDef *GPIOx,u16 GPIO_Pin_x)
{
		int keyPort=0;
		EzhKeyEvent event;
		//��ȡGPIOA��I/O��ƽ
		keyPort=GPIO_ReadInputData(GPIOx); 
		keyPort=keyPort&GPIO_Pin_x;
		keyPort=!keyPort;
		switch(*status)
		{
				/*ʹ��switch�жϼ���Ƿ�Ϊ�����ź�,������Ǳ㼴�в���*/
				case ZH_KEY_STATE_1:
				{
				 //�Ƕ������в���
				 if(keyPort)
				 {
						event=ZH_KEY_EVENT_DOWN;
				//�л�״̬
				 *status=ZH_KEY_STATE_2;
				 }
				 else
				 {
					 event=ZH_KEY_EVENT_NONE; 
				 *status=ZH_KEY_STATE_0;
				 }
				}
				break;
				/*��ѹ���*/
				case ZH_KEY_STATE_2:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
				 *status=ZH_KEY_STATE_3;
					}
					else
					{
						 //�Ѿ�����,����״̬
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				/*���ּ��*/
				case ZH_KEY_STATE_3:
				{
					if(keyPort)
					{
					 event=ZH_KEY_EVENT_PRESS;
					}
					else
					{
						 //�Ѿ�����,����״̬
						 *status=ZH_KEY_STATE_0;
				 event=ZH_KEY_EVENT_UP;
					}
				}
				break;
				default:
				{
							//�е�ƽ�ź�����
							if(keyPort)
							{
									*status=ZH_KEY_STATE_1; 
							}
							event=ZH_KEY_EVENT_NONE;
				}
				break;
		}
		return event;
}



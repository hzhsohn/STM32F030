#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "output.h"
#include "USART1.h"
#include "ds18b20.h"
#include "key.h"
#include "flash_rw.h"

//------------------------------------------------------
//����
EzhKeyEvent ev;
EzhKeyState GPIOAStatus1;//һ��GPIO��Ӧһ��EzhKeyState����
EzhKeyState GPIOAStatus2;
//-----------------------------------------------------
//�¶�
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0;
int isCheckWaterSensorErr=0; 
u32 gettemp=0;
//����¶�ֵ
int monitor_temperat_val=0;
//-----------------------------------------------------
void udoTemperature_cb(s16 temperature)
{
	printf("{\"temperature\":%0.1f,\"trigger\":%0.1f}",temperature*0.1f,monitor_temperat_val*0.1f);
	//�̵�������
	if(temperature<monitor_temperat_val)
	{
		OUTP1_SET(1);
	}
	else
	{
		OUTP1_SET(0);
	}
	//���ȿ���
	if(temperature<monitor_temperat_val)
	{		
		OUTP2_SET(1);
	}
	else	
	{
		//���ȶ�ʱ����ת��
		static int nnn=0;
		nnn++;
		if(nnn<10*3)
		{
			OUTP2_SET(0);
		}		
		else
		{
			OUTP2_SET(1);
			if(nnn>10*4)
			{
				nnn=0;			
			}
		}
	}
}
void udoTemperatureErr_cb()
{
	printf("temperature err\r\n");
	OUTP1_SET(0);
}

void TemperatureProc()
{
	rWaterTemp=DS18B20_Get_Temp();
	//printf("%d\r\n",rWaterTemp);
	if(rWaterTemp<2000 && rWaterTemp> -200) //����λ
	{
		ntmp=rWaterTemp-rWaterTemperature;
		if(ntmp<20 && ntmp>-20)	//����ͻ�����
		{     
			udoTemperature_cb(rWaterTemp);
			isCheckWaterSensorErr=0;
		}
		rWaterTemperature=rWaterTemp;
	}
	else
	{
		isCheckWaterSensorErr++;						
		if(isCheckWaterSensorErr>10) //��������ë��̫��ص����ȼ̵���
		{
			//��������ë����
			udoTemperatureErr_cb();
		}
	}
}

int main(void)
{
  delay_init();
	DS18B20_Init();
  LED_Init();
	OUTPUT_Init();
  USART1_Init(115200);	
	//��ʼ������
	zhSCM_GPIOConfig(GPIOA, GPIO_Pin_3); 
	zhSCM_GPIOConfig(GPIOA, GPIO_Pin_4); 
	zhSCM_initKeyState(&GPIOAStatus1);
	zhSCM_initKeyState(&GPIOAStatus2);
	//�����¶�
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&monitor_temperat_val,sizeof(monitor_temperat_val));
	if(monitor_temperat_val<10 || monitor_temperat_val>1000)
	{
		//�¶Ȳ���������Χ����ΪĬ��ֵ
		monitor_temperat_val=380; //Ĭ�ϴ����¶�38��
		FLASH_WriteByte(STARTADDR,(uint8_t*)&monitor_temperat_val,sizeof(monitor_temperat_val));
	}
	//printf("monitor_temperat_val=%d",monitor_temperat_val);
	//
	printf("{\"system:\":\"startup\"}");
		
  while (1)
  {
		//�¶�
    if(gettemp>200000)
		{
			LED1_SET(1);//LED��
			TemperatureProc();
			gettemp=0;
		}		
		LED1_SET(0);//LED��
		gettemp++;
		
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
					monitor_temperat_val-=1; 
					FLASH_WriteByte(STARTADDR,(uint8_t*)&monitor_temperat_val,sizeof(monitor_temperat_val));
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
					monitor_temperat_val+=1; 
					FLASH_WriteByte(STARTADDR,(uint8_t*)&monitor_temperat_val,sizeof(monitor_temperat_val));
        break;
    }
  }
 
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

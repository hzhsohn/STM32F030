#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f0xx.h"

#define u8_t unsigned char
#define u8 unsigned char
#define u32_t unsigned int
#define u16_t unsigned short
#define s16 short


#define DS_RCC_AHB_GPIO	RCC_AHBPeriph_GPIOA
#define DS18B20_DQ_GPIO 	    GPIOA
#define DS18B20_DQ_PIN  	    GPIO_Pin_2

#define DS18B20_DQ_STATE(x) (x)>0?GPIO_SetBits(DS18B20_DQ_GPIO,DS18B20_DQ_PIN):GPIO_ResetBits(DS18B20_DQ_GPIO,DS18B20_DQ_PIN)
#define DS18B20_DQ_GET() GPIO_ReadInputDataBit(DS18B20_DQ_GPIO,DS18B20_DQ_PIN)
u8 DS18B20_Init(void);			//��ʼ��DS18B20
s16 DS18B20_Get_Temp(void);		//��ȡ�¶�
void DS18B20_Start(void);			//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20 

#endif

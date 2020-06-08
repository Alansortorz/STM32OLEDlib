#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h" 	 
#include "bsp_systick.h"
#include <string.h>
#include <stdio.h>

/**
  * OLEDģʽ����
	* 0:4�ߴ���ģʽ
	* 1:����8080ģʽ
  */
#define OLED_MODE 				0
#define SIZE 							16
#define XLevelL						0x00
#define XLevelH						0x10
#define Max_Column				128
#define Max_Row						64
#define	Brightness				0xFF 
#define X_WIDTH 					128
#define Y_WIDTH 					64	    

#define OLED_CMD  0				//д����
#define OLED_DATA 1				//д����

/* �˿����ź궨��,���������ֲ */
#define  GPIO_OLED_CLK  				RCC_APB2Periph_GPIOC
#define  GPIO_OLED_SCLK_Pin     GPIO_Pin_0							/* D0 */
#define  GPIO_OLED_PIN_Pin     	GPIO_Pin_1							/* D1 */
#define  GPIO_OLED_RES_Pin     	GPIO_Pin_2							/* RES */
#define  GPIO_OLED_DC_Pin     	GPIO_Pin_3							/* DC */

/* ���ŵ�ƽ���� */
/** 
  * ע�⣺��Ҫ���õ���RES��DC��CLK��PIN�ĸ����ţ�����CS�ɲ��ӣ���ѡģʽ0��ʱ��Ҫ��CS
	*/
/*
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)	//CS Ƭѡ => ��������� ��ѡģʽ0��ʱ��Ҫ��
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)
*/

#define OLED_RST_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_2)	//RES RES => ��RES����
#define OLED_RST_Set() GPIO_SetBits(GPIOC,GPIO_Pin_2)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_3)	//DC  DC  => ��DC���� 
#define OLED_DC_Set() GPIO_SetBits(GPIOC,GPIO_Pin_3)

/* ʹ��4�ߴ��нӿ�ʱʹ�� */ 
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_0)//CLK D0  => ��D0����
#define OLED_SCLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_0)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_1)//PIN D1  => ��D1����
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_1)
  
/* PC0~7,��Ϊ������ */
#define DATAOUT(x) GPIO_Write(GPIOB,x);									//��� 

/* OLED�����ú��� */
void OLED_Clear(void);																																											 /* OLED���� */
void OLED_Display_On(void);                                                                                  /* OLED�� */
void OLED_ShowPosture(void);																																								 /* ��ʾ��Ϣ */
void OLED_Display_Off(void);                                                                                 /* OLED�� */
void GPIO_OLED_InitConfig(void);                                                                             /* OLED��ʼ�� */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	                                                                 /* д�ֽ� */
void OLED_Set_Pos(unsigned char x, unsigned char y);                                                         /* �������� */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);                                                         /* ��ʾ�ַ� */
void OLED_ShowString(uint8_t x,uint8_t y, char *p);	                                                     		 /* ��ʾ�ַ��� */
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);                                                       /* ��ʾ���� */
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size);                                     /* ��ʾ���� */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);/* ��ʾͼƬ */
void Board_MPU_Angle_Show(void);
void Platform_MPU_Angle_Show(void);
void Lipo_Voltage_Display(void);
void DHT11_TemHum_Display(void);
void USB_ON_Dispaly(void);
void USB_OFF_Dispaly(void);

#endif  /* __OLED_H */
	 




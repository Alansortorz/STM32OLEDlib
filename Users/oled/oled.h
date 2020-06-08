#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h" 	 
#include "bsp_systick.h"
#include <string.h>
#include <stdio.h>

/**
  * OLED模式设置
	* 0:4线串行模式
	* 1:并行8080模式
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

#define OLED_CMD  0				//写命令
#define OLED_DATA 1				//写数据

/* 端口引脚宏定义,方便程序移植 */
#define  GPIO_OLED_CLK  				RCC_APB2Periph_GPIOC
#define  GPIO_OLED_SCLK_Pin     GPIO_Pin_0							/* D0 */
#define  GPIO_OLED_PIN_Pin     	GPIO_Pin_1							/* D1 */
#define  GPIO_OLED_RES_Pin     	GPIO_Pin_2							/* RES */
#define  GPIO_OLED_DC_Pin     	GPIO_Pin_3							/* DC */

/* 引脚电平设置 */
/** 
  * 注意：需要配置的有RES、DC、CLK、PIN四个引脚，接线CS可不接，当选模式0的时候要接CS
	*/
/*
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)	//CS 片选 => 置零或悬空 当选模式0的时候要连
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)
*/

#define OLED_RST_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_2)	//RES RES => 接RES引脚
#define OLED_RST_Set() GPIO_SetBits(GPIOC,GPIO_Pin_2)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_3)	//DC  DC  => 接DC引脚 
#define OLED_DC_Set() GPIO_SetBits(GPIOC,GPIO_Pin_3)

/* 使用4线串行接口时使用 */ 
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_0)//CLK D0  => 接D0引脚
#define OLED_SCLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_0)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_1)//PIN D1  => 接D1引脚
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_1)
  
/* PC0~7,作为数据线 */
#define DATAOUT(x) GPIO_Write(GPIOB,x);									//输出 

/* OLED控制用函数 */
void OLED_Clear(void);																																											 /* OLED清屏 */
void OLED_Display_On(void);                                                                                  /* OLED开 */
void OLED_ShowPosture(void);																																								 /* 提示信息 */
void OLED_Display_Off(void);                                                                                 /* OLED关 */
void GPIO_OLED_InitConfig(void);                                                                             /* OLED初始化 */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	                                                                 /* 写字节 */
void OLED_Set_Pos(unsigned char x, unsigned char y);                                                         /* 设置坐标 */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);                                                         /* 显示字符 */
void OLED_ShowString(uint8_t x,uint8_t y, char *p);	                                                     		 /* 显示字符串 */
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);                                                       /* 显示中文 */
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size);                                     /* 显示数字 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);/* 显示图片 */
void Board_MPU_Angle_Show(void);
void Platform_MPU_Angle_Show(void);
void Lipo_Voltage_Display(void);
void DHT11_TemHum_Display(void);
void USB_ON_Dispaly(void);
void USB_OFF_Dispaly(void);

#endif  /* __OLED_H */
	 




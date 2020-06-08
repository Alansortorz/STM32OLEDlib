/*************************************************************
 *	时间：2018.12.19   
 *  地点：厦门大学航空航天学院484实验室 自动化系
 *	程序名称：0.96寸OLED驱动程序
 *	版本：1.0
 *
 **************************************************************/
/** 注意：1、头文件oledfont.h的声明必须放在该文件内，否则在整个工程
  * 编译时会报重复定义错误！
	*       2、头文件bmp.h不应该在此声明，而应该在调用bmp图片的函数文
	* 件中声明！
	*       3、OLED显示格式范围：x 0-127    y 0-7
  */
#include "oled.h"	   
#include "oledfont.h" 
	
#if OLED_MODE==1
/**
  * @brief 向SSD1106写入一个字节
	* @param dat:要写入的数据/命令  cmd:数据/命令标志 0,表示命令;1,表示数据
	* @retval None
  */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	DATAOUT(dat);	    
	if(cmd)
	  OLED_DC_Set();
	else 
		OLED_DC_Clr();		   
	OLED_CS_Clr();
	OLED_WR_Clr();	 
	OLED_WR_Set();
	OLED_CS_Set();	  
	OLED_DC_Set();	 
} 	    	    
#else

/**
  * @brief 向SSD1106写入一个字节
	* @param dat:要写入的数据/命令 cmd:数据/命令标志 0,表示命令;1,表示数据;
	* @retval None
  */
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_DC_Set();   	  
} 
#endif

/**
  * @brief 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
	* @param None
	* @retval None
  */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   

/**
  * @brief 开启OLED显示
	* @param None
	* @retval None
  */ 
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/**
  * @brief 关闭OLED显示    
	* @param None
	* @retval None
  */   
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		

/**
  * @brief 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
	* @param None
	* @retval None
  */
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	}																		 //更新显示
}

/**
  * @brief 在指定位置显示一个字符,包括部分字符
	* @param x:0~127   y:0~63   mode:0,反白显示  1,正常显示	 size:选择字体 16/12 
	* @retval None
  */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';														//得到偏移后的值			
	if(x>Max_Column-1)
	{
		x=0;
		y=y+2;
	}
	if(SIZE==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(D8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(D8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
		{
			OLED_WR_Byte(D6X8[c][i],OLED_DATA);
		}
	}
}

/**
  * @brief m^n函数
	* @param None
	* @retval None
  */
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}		

/**
  * @brief 显示2个数字
	* @param x,y :起点坐标
	*				 len :数字的位数，即显示几位有效数字
  *				 size:字体大小
  *				 mode:模式	0,填充模式;1,叠加模式
  *        num:数值(0~4294967295);
	* @retval None
  */ 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

/**
  * @brief 显示一个字符号串
	* @param 
	* @retval None
  */
void OLED_ShowString(uint8_t x,uint8_t y,char *chr)
{
	unsigned char j=0;
	while(chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

/**
  * @brief 显示汉字
	* @param 
	* @retval None
  */
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<32;t++)
		{
				OLED_WR_Byte(SHOW[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<32;t++)
			{	
				OLED_WR_Byte(SHOW[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

/**
  * @brief 显示显示BMP图片
	* @param 显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
	* @retval None
  */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

/**
  * @brief 初始化SSD1306
	* @param None
	* @retval None
  */				    
void GPIO_OLED_InitConfig(void)
{ 	
	GPIO_InitTypeDef GPIO_OLEDInitStruct;                        						//定义一个GPIO口初始化结构体ledInitStruct
	RCC_APB2PeriphClockCmd(GPIO_OLED_CLK, ENABLE);  									      //GPIOB端口RCC时钟使能
	GPIO_OLEDInitStruct.GPIO_Pin = GPIO_OLED_SCLK_Pin | GPIO_OLED_PIN_Pin |
																 GPIO_OLED_RES_Pin  | GPIO_OLED_DC_Pin;   //指定引脚为12和13
	GPIO_OLEDInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;						 						//配置成输出模式
	GPIO_OLEDInitStruct.GPIO_Speed = GPIO_Speed_50MHz;           						//传输速率配置成50HZ
	GPIO_Init(GPIOC, &GPIO_OLEDInitStruct);                      						//调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO 	
 	GPIO_SetBits(GPIOB, GPIO_OLED_SCLK_Pin|GPIO_OLED_PIN_Pin|GPIO_OLED_RES_Pin|GPIO_OLED_DC_Pin);

  OLED_RST_Set();
	Delay_ms(100);
	OLED_RST_Clr();
	Delay_ms(100);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  





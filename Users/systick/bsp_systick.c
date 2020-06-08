#include "bsp_systick.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数

/**
  * @brief 系统时钟SysTick初始化函数
	* @param None   
	* @retval None
  */
void Systick_InitConfig(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;	
}

/**
  * @brief 微秒(us)延时函数
	* @param nus：时间(单位为us)    
	* @retval None
  */
void Delay_us(uint32_t nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 								//时间加载	  		 
	SysTick->VAL=0x00;        								//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 				//清空计数器	 
}

/**
  * @brief 毫秒(ms)延时函数
	* @param nms：时间(单位为ms)   
	* @retval None
  */
void Delay_ms(uint16_t nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				    //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							          //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		  //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       								//清空计数器	  	    
} 


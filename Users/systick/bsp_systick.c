#include "bsp_systick.h"

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������

/**
  * @brief ϵͳʱ��SysTick��ʼ������
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
  * @brief ΢��(us)��ʱ����
	* @param nus��ʱ��(��λΪus)    
	* @retval None
  */
void Delay_us(uint32_t nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 								//ʱ�����	  		 
	SysTick->VAL=0x00;        								//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 				//��ռ�����	 
}

/**
  * @brief ����(ms)��ʱ����
	* @param nms��ʱ��(��λΪms)   
	* @retval None
  */
void Delay_ms(uint16_t nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				    //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							          //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		  //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       								//��ռ�����	  	    
} 


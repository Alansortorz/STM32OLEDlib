/*************************************************************
 *	时间：2018.12.19   
 *  地点：厦门大学航空航天学院484实验室 自动化系
 *	程序名称：0.96寸OLED驱动主程序
 *	版本：1.0
 *
 **************************************************************/
#include "stm32f10x.h"
#include "oled.h"
#include "bsp_systick.h"
#include "bmp.h"

int main(void)
{
	Systick_InitConfig();
	GPIO_OLED_InitConfig();
	
	/** @brief 0.96寸OLED测试主程序核心代码
	  *	@note 请在此处添加你的测试代码，各文件的注意事项请参阅相关文件的注释
	  * 程序已经调试完毕，可直接编译运行
		*/
	OLED_Clear();
	OLED_DrawBMP(0,0,126,8,BMP);
	
	while(1);
}

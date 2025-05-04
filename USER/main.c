#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "w25qxx.h"
#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include "usbd_msc_bot.h"
/************************************************
 ALIENTEK 探索者STM32F407开发板 实验13
 LCD显示实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

USB_OTG_CORE_HANDLE USB_OTG_dev;

int main(void)
{
	u8 x=0;
	u8 lcd_id[12];				//存放LCD ID字符串
	
    HAL_Init();                   	//初始化HAL库    
    Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	LED_Init();						//初始化LED	
	W25QXX_Init();					//初始化W25Q128 
 	LCD_Init();           			//初始化LCD FSMC接口
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	POINT_COLOR=RED;     			//画笔颜色：红色
	LCD_ShowString(30,40,210,24,24,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 	LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
	LCD_ShowString(30,130,200,12,12,"2025/5/4");	 
	
	if(W25QXX_ReadID()!=W25Q128 && W25QXX_ReadID()!=NM25Q128 && W25QXX_ReadID()!=BY25Q128)  //检测W25Q128错误
		LCD_ShowString(30,130,200,16,16,"W25Q128 Error!");
	else //SPI FLASH 正常
	{   														 
		LCD_ShowString(30,150,200,16,16,"SPI FLASH OK!");	 
	}  
	
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_MSC_cb,&USR_cb);
	
  	while(1) 
	{		 
		x++;
		if(x==12)x=0;
		LED0=!LED0;	 
		delay_ms(1000);	
	} 
}


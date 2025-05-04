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
 ALIENTEK ̽����STM32F407������ ʵ��13
 LCD��ʾʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

USB_OTG_CORE_HANDLE USB_OTG_dev;

int main(void)
{
	u8 x=0;
	u8 lcd_id[12];				//���LCD ID�ַ���
	
    HAL_Init();                   	//��ʼ��HAL��    
    Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	LED_Init();						//��ʼ��LED	
	W25QXX_Init();					//��ʼ��W25Q128 
 	LCD_Init();           			//��ʼ��LCD FSMC�ӿ�
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
	POINT_COLOR=RED;     			//������ɫ����ɫ
	LCD_ShowString(30,40,210,24,24,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 	LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
	LCD_ShowString(30,130,200,12,12,"2025/5/4");	 
	
	if(W25QXX_ReadID()!=W25Q128 && W25QXX_ReadID()!=NM25Q128 && W25QXX_ReadID()!=BY25Q128)  //���W25Q128����
		LCD_ShowString(30,130,200,16,16,"W25Q128 Error!");
	else //SPI FLASH ����
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


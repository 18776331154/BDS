//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : Evk123
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）            
//              ----------------------------------------------------------------
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"

int num=0;
char a='a';
char string[100] = "$GNGGA,095528.000,2318.1133,N,11319.7210,E,1,06";
 int main(void)
  {
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		initial_lcd();		//初始化OLED  
		OLED_Clear() ; 
	
	while(1) 
	{		
		num++;
		if(num==10000)num=0;
		OLED_ShowChar(3,0,a,16);
		OLED_ShowNum(20,0,num,5,16);
		OLED_ShowCHinese(70,0,0);
		OLED_ShowCHinese(86,0,1);
		OLED_ShowCHinese(102,0,2);
		OLED_ShowString(0,2,string,16);

	}	  
	
}
	
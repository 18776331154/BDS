//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : Evk123
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.69��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��            
//              ----------------------------------------------------------------
//Copyright(C) �о�԰����2014/3/16
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
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
		initial_lcd();		//��ʼ��OLED  
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
	
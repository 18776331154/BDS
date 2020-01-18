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
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
/**********************************************
//IIC Start
**********************************************/
/**********************************************
//IIC Start
**********************************************/

void OLED_WR_Byte(unsigned int dat,unsigned int cmd)
{
	if(cmd)
		{
			transfer_data_lcd(dat);				

		}
	else 
		{
			transfer_command_lcd(dat); 
		}


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//坐标设置

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	unsigned char i,j;
	lcd_cs1(0);
	Rom_CS(1);	
	for(i=0;i<8;i++)
	{
		transfer_command_lcd(0xb0+i);
		transfer_command_lcd(0x00);
		transfer_command_lcd(0x10);
		for(j=0;j<128;j++)
		{
		  	transfer_data_lcd(0x00);
		}
	}
 	lcd_cs1(1);

}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}

//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
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

//初始化SSD1306					    
void initial_lcd(void)
{
	delay_ms(400);
	//OLED_GPIO_Config();
	GBZK_GPIO_Config();
	lcd_cs1(0);
	Rom_CS(1);
       
	transfer_command_lcd(0xAE);   //display off
	transfer_command_lcd(0x20);	//Set Memory Addressing Mode	
	transfer_command_lcd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	transfer_command_lcd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	transfer_command_lcd(0xc8);	//Set COM Output Scan Direction
	transfer_command_lcd(0x00);//---set low column address
	transfer_command_lcd(0x10);//---set high column address
	transfer_command_lcd(0x40);//--set start line address
	transfer_command_lcd(0x81);//--set contrast control register
	transfer_command_lcd(0xFF);
	transfer_command_lcd(0xa1);//--set segment re-map 0 to 127
	transfer_command_lcd(0xa6);//--set normal display
	transfer_command_lcd(0xa8);//--set multiplex ratio(1 to 64)
	transfer_command_lcd(0x3F);//
	transfer_command_lcd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	transfer_command_lcd(0xd3);//-set display offset
	transfer_command_lcd(0x00);//-not offset
	transfer_command_lcd(0xd5);//--set display clock divide ratio/oscillator frequency
	transfer_command_lcd(0xf0);//--set divide ratio
	transfer_command_lcd(0xd9);//--set pre-charge period
	transfer_command_lcd(0x22); //
	transfer_command_lcd(0xda);//--set com pins hardware configuration
	transfer_command_lcd(0x12);
	transfer_command_lcd(0xdb);//--set vcomh
	transfer_command_lcd(0x20);//0x20,0.77xVcc
	transfer_command_lcd(0x8d);//--set DC-DC enable
	transfer_command_lcd(0x14);//
	transfer_command_lcd(0xaf);//--turn on oled panel 
	lcd_cs1(1);
}



void GBZK_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOC的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

	/*选择要控制的GPIOC引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 ;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	/* 关闭所有led灯	*/
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 );	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10 );
	
		/*开启GPIOC的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

	/*选择要控制的GPIOC引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  

	/* 关闭所有led灯	*/
	GPIO_ResetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 );	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4 );
	
}


/*写指令到LCD模块*/
void transfer_command_lcd(int data1)   
{
	char i;
	lcd_rs(0);;;
	lcd_cs1(0);
	for(i=0;i<8;i++)
   {lcd_sclk(0);;;
		
		if(data1&0x80) {lcd_sid(1);;;}
		else {lcd_sid(0);;;}
		lcd_sclk(1);
		__nop();;;
	//	lcd_sclk(0);;;
	 	data1<<=1;
   }
	 	lcd_rs(1);;;
	 lcd_cs1(1);
}

/*写数据到LCD模块*/
void transfer_data_lcd(int data1)
{
	char i;
	lcd_rs(1);;;
	lcd_cs1(0);
	for(i=0;i<8;i++)
   {
		lcd_sclk(0);;;
		if(data1&0x80) {lcd_sid(1);;;}
		else {lcd_sid(0);;;}
		lcd_sclk(1);;;
		__nop();;;
		//lcd_sclk(0);;;
	 	data1<<=1;
   }lcd_rs(1);;;
	 lcd_cs1(1);
}



//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}


void display_graphic_16x16(int page,int column,const char *dp)
{
	int i,j;
 	lcd_cs1(0);
	Rom_CS(1); 	
	for(j=2;j>0;j--)
	{
		lcd_address(column,page);
		for (i=0;i<16;i++)
		{	
			transfer_data_lcd(*dp);					/*D′êy?Yμ?LCD,??D′íêò???8??μ?êy?YoóáDμ??·×??ˉ?ó1*/
			dp++;
		}
		page++;
	}
	lcd_cs1(1);
}
void lcd_address(char page,char column)
{

	transfer_command_lcd(0xb0 + column);   /*éè??ò3μ??·*/
	transfer_command_lcd(((page & 0xf0) >> 4) | 0x10);	/*éè??áDμ??·μ???4??*/
	transfer_command_lcd((page & 0x0f) | 0x00);	/*éè??áDμ??·μ?μí4??*/	
}











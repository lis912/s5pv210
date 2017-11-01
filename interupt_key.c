#include "stdio.h"
#include "key.h"
#include "led.h"


// 初始化按键GPIO为中断模式
void key_init_int(void)
{
	// 设置GPIO为中断模式
	rGPH0CON &= ~(0xFF<<8);
	rGPH0CON |= (0xFF<<8);
	rGPH2CON &= ~(0xFFFF<<0);
	rGPH2CON |= (0xFFFF<<0);
}

// 初始按键相关的化外部中断
void eint_init(void)
{
	key_init_int();
	
	// 设置按键中断触发方式：统一为下降沿触发,也就是按下的时候！
	rEXT_INT_0_CON &= ~((7<<8) | (7<<12));
	rEXT_INT_0_CON |= ((FALLING_EDGE_TRIGGE<<8) | (FALLING_EDGE_TRIGGE<<12));
	rEXT_INT_2_CON &= ~(0xffff<<0);
	rEXT_INT_2_CON |= ((FALLING_EDGE_TRIGGE<<0)|(FALLING_EDGE_TRIGGE<<4)|(FALLING_EDGE_TRIGGE<<8)|(FALLING_EDGE_TRIGGE<<12));
	
	// 清中断挂起位,此寄存器是中断标志位，1表示中断发生，0表示无发生，初始化为0
	rEXT_INT_0_PEND &= ~(1<<2 | 1<<3);
	rEXT_INT_2_PEND &= ~(0x0f<<0);
	
	// 使能/禁止 外部中断
	rEXT_INT_0_MASK &= ~(3<<2);
	rEXT_INT_2_MASK &= ~(0x0f<<0);
}

// 下面全是按键中断的ISR处理函数
void key_isr_eint2(void)
{	
	// 手动清挂起，写1清挂起
	rEXT_INT_0_PEND |= (1<<2);
	
	printf("eint2 key LEFT.\n");
}

void key_isr_eint3(void)
{
	rEXT_INT_0_PEND |= (1<<3);
	
	printf("eint3 key DOWN.\n");
}

void key_isr_eint16171819(void)
{
	if (rEXT_INT_2_PEND & (1<<0))
	{
		printf("eint16 key UP.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<1))
	{
		printf("eint17 key RIGHT.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<2))
	{
		printf("eint18 key BACK.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<3))
	{
		printf("eint19 key MENU.\n");
	}
	
	rEXT_INT_2_PEND |= (0x0f<<0);
}




















#include "stdio.h"
#include "key.h"

// 初始化按键
void key_init(void)
{
	// 设置GPHxCON寄存器，设置为输入模式
	// GPH0CON的bit8～15全部设置为0，即可
	rGPH0CON &= ~(0xFF<<8);
	// GPH2CON的bit0～15全部设置为0，即可
	rGPH2CON &= ~(0xFFFF<<0);
}

void delay20ms(void)
{
	// 这个函数作用是延时20ms
	// 因为我们这里是裸机程序，且重点不是真的要消抖，而是教学
	// 所以我这里这个程序只是象征性的，并没有实体
	// 如果是研发，那就要花时间真的调试出延时20ms的程序
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}

// 按键显示键名+延时消抖
void key_polling(void)
{
	// 依次，挨个去读出每个GPIO的值，判断其值为1还是0.如果为1则按键按下，为0则弹起
	
	// 轮询的意思就是反复循环判断有无按键，隔很短时间
	while (1)
	{
		// 对应开发板上标着LEFT的那个按键
		if (rGPH0DAT & (1<<2))
		{
			// 为1，说明没有按键
		}
		else
		{
			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH0DAT & (1<<2)))
			{
				// 为0，说明有按键
				printf("key left.\n");
			}
		}
		
		
		// 对应开发板上标着DOWN的那个按键
		if (rGPH0DAT & (1<<3))
		{
			// 为1，说明没有按键
		}
		else
		{
			// 为0，说明有按键
			printf("key down.\n");
		}
		
		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<0))
		{
			// 为1，说明没有按键
			//led_off();
		}
		else
		{
			// 为0，说明有按键
			printf("key UP.\n");
		}
		
		if (rGPH2DAT & (1<<1))
		{
			
		}
		else
		{
			printf("key RIGHT.\n");
		}
		
		if (rGPH2DAT & (1<<2))
		{
			
		}
		else
		{
			printf("key BACK.\n");
		}
		
		if (rGPH2DAT & (1<<3))
		{
			
		}
		else
		{
			printf("key MENU.\n");
		}
	}
}


























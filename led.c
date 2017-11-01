#include "main.h"





// led初始化
void led_init(void)
{
	// led初始化，也就是把GPJ0CON中设置为输出模式
	rGPJ0CON = 0x11111111;
	
	// 另外一颗D25配置为输出模式
	rGPD0CON_2 &= ~(0xf<<4);
	rGPD0CON_2 |= (0x1<<4);
	
}

// 配置D25输出低电平点亮！
void led_d25on(void)
{
	rGPD0DAT |= (0<<1);
}

// 全部点亮
void led_all_on(void)
{
	rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
	rGPD0DAT |= (0<<1);
}

// 全部熄灭
void led_all_off(void)
{
	rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
	rGPD0DAT |= (1<<1);
}

/*
// 指定点亮某一颗led,不管led灯原来是什么状态
void led_select(int i)
{	
	switch (i)
	{
		case 1:
		rGPJ0DAT = ((0<<3);
		break;
		
		case 2:
		rGPJ0DAT = ((0<<4);
		break;
		
		case 3:
		rGPJ0DAT = ((0<<5);
		break;
		
		case 4:
		rGPD0DAT |= (0<<1);
		break;
		
		default:
		printf("usage: The argument limits must 1~4 ");
		break;
	}
}
*/

// 该函数要实现led闪烁效果
void led_blink(void)
{
	// led初始化，也就是把GPJ0CON中设置为输出模式
	//volatile unsigned int *p = (unsigned int *)GPJ0CON;
	//volatile unsigned int *p1 = (unsigned int *)GPJ0DAT;
	rGPJ0CON = 0x11111111;
	
	while (1)
	{
		// led亮
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
		rGPD0DAT |= (0<<1);
		// 延时
		delays(1);
		// led灭
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
		rGPD0DAT |= (1<<1);
		// 延时
		delays(1);
	}
}


// 花式闪灯
void led_figure (void)
{
	while(1)
	{
		unsigned int i;
		// 闪8轮跑马灯循环
		for(i=0; i<8; i++)
		{
			rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
			delays(100);
		}
		// 全亮全灭8次
		for (i=0; i<8; i++)
		{
			rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
			delays(100);
		}
	}
	 
}

// 跑马灯
void led_paomadeng(void)
{
	while(1)
	{
		rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
		delays(100);
		rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
		delays(100);
		rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
		delays(100);
	}
}	



int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc == 2)
	{
		if (!strcmp(argv[1], "on"))
		{
			led_all_on();
		}
		else if (!strcmp(argv[1], "off"))
		{
			led_all_off();
		}
		else
		{
			printf ("Usage:\n%s\n", cmdtp->usage);
			return 1;
		}
			
	}

	return 0;
}


#include "main.h"

void init_time3(int hz)
{
	// 设置GPD0_2引脚，将其配置为XpwmTOUT_2
	rGPD0CON &= ~(0xf<<12);
	rGPD0CON |= (2<<12);
	
	// 设置PWM定时器的一干寄存器，使其工作
	rTCFG0 &= ~(0xff<<8);
	rTCFG0 |= (65<<8);			// prescaler1 = 65, 预分频后频率为1MHz
	
	rTCFG1 &= ~(0x0f<<12);
	rTCFG1 |= (0<<12);			// 1Mhz 也就是 1us 
	
	rCON |= (1<<19);		// 使能auto-reload，反复定时才能发出PWM波形
							// 即便不使能，经过测试也是可用的
							
	rTCNTB3 = hz;			// 0.5ms/2us = 500us/2us = 250
	//rTCMPB3 = 125;			// duty = 50%
							// 疑惑的是我把rTCMPB2也就是说没有电平反转照样能驱动蜂鸣器
							// 在LED试验驱动D25的时候就误把蜂鸣器也驱动了！
		
	
	// 第一次需要手工将TCNTB中的值刷新到TCNT中去，以后就可以auto-reload了
	rCON |= (1<<17);		// 打开自动刷新功能
	rCON &= ~(1<<17);		// 关闭自动刷新功能
}

// 秒级 延时函数
void delays(unsigned int time)
{
	// 获取系统PSYS域，PCLK的时钟频率
	
	// 计算 经过分频设置后，得到定时器为1Khz的频率，也就是1ms周期，如果是s是
	// 计算过了，无法将频率降到那么小，只能是1Mhz了，将来time*1000就行可
	init_time3(S);
	
	
	// 进入循环读取计时器的值，直到为0时候退出，这样time是多少延时就是多少了
	// 
	rCON |= (1<<16);		// 开timer2定时器。要先把其他都设置好才能开定时器
	while (time--)			// 循环体每执行一次为1s
	{
		
		while (rTCNTO3);
		//printf(" %d ", time);
	}
		
}

// 毫秒级 延时函数
void delayms(unsigned int time)
{
	// 获取系统PSYS域，PCLK的时钟频率
	
	// 计算 经过分频设置后，得到定时器为1Khz的频率，也就是1ms周期，如果是s是
	// 计算过了，无法将频率降到那么小，只能是1Mhz了，将来time*1000就行可
	init_time3(MS);
	
	
	// 进入循环读取计时器的值，直到为0时候退出，这样time是多少延时就是多少了
	// 
	rCON |= (1<<16);		// 开timer2定时器。要先把其他都设置好才能开定时器
	while (time--)			// 循环体每执行一次为1s
	{
		
		while (rTCNTO3);
		//printf(" %d ", time);
	}
		
}

// 微秒级 延时函数
void delayus(unsigned int time)
{
	// 获取系统PSYS域，PCLK的时钟频率
	
	// 计算 经过分频设置后，得到定时器为1Khz的频率，也就是1ms周期，如果是s是
	// 计算过了，无法将频率降到那么小，只能是1Mhz了，将来time*1000就行可
	init_time3(US);
	
	
	// 进入循环读取计时器的值，直到为0时候退出，这样time是多少延时就是多少了
	// 
	rCON |= (1<<16);		// 开timer2定时器。要先把其他都设置好才能开定时器
	while (time--)			// 循环体每执行一次为1s
	{
		
		while (rTCNTO3);
		//printf(" %d ", time);
	}
		
}










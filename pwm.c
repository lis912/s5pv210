#include "pwm.h"
#include "stdio.h"



// 初始化PWM timer2，使其输出PWM波形：频率是2KHz、duty为50%
void timer2_pwm_init(void)
{
	// 设置GPD0_2引脚，将其配置为XpwmTOUT_2
	rGPD0CON &= ~(0xf<<8);
	rGPD0CON |= (2<<8);
	
	// 设置PWM定时器的一干寄存器，使其工作
	rTCFG0 &= ~(0xff<<8);
	rTCFG0 |= (65<<8);			// prescaler1 = 65, 预分频后频率为1MHz
	
	rTCFG1 &= ~(0x0f<<8);
	rTCFG1 |= (1<<8);			// MUX2设置为1/2,分频后时钟周期为500KHz
	// 时钟设置好，我们的时钟频率是500KHz，对应的时钟周期是2us。也就是说每隔2us
	// 计一次数。如果要定的时间是x，则TCNTB中应该写入x/2us
	
	rCON |= (1<<15);		// 使能auto-reload，反复定时才能发出PWM波形
							// 即便不使能，经过测试也是可用的
							
	rTCNTB2 = 250;			// 0.5ms/2us = 500us/2us = 250
	rTCMPB2 = 125;			// duty = 50%
							// 疑惑的是我把rTCMPB2也就是说没有电平反转照样能驱动蜂鸣器
							// 在LED试验驱动D25的时候就误把蜂鸣器也驱动了！
	

	
	
	// 第一次需要手工将TCNTB中的值刷新到TCNT中去，以后就可以auto-reload了
	rCON |= (1<<13);		// 打开自动刷新功能
	rCON &= ~(1<<13);		// 关闭自动刷新功能
	
	rCON |= (1<<12);		// 开timer2定时器。要先把其他都设置好才能开定时器
	
	while(rTCNTO2)
		printf(" %d  ", rTCNTO2);
}















#include "main.h"

unsigned int yes_press = 1;
unsigned int no_press = 0;


// 实现功能: 自动倒计时，和按下任意键 进入shell界面
void shell_bootdealy(unsigned int count_down)
{
	printf("Press any key to enter shell: ");
	// 逻辑解释：无输入按下=真 && 倒计时不是0=真 	while阻塞 
	while ((!(is_key_press() == yes_press)) && (!(count_down == 0)))
	{
		printf("%d", count_down);		// 打印当前倒计时
		shell_putc('\b');				// 把光标退到前一个字符上
		delays(1);						// 延时1s
		--count_down;					// 倒计时--
	}
}

// 检测串口是否有接收到内容，也就是检测是否有任意按键按下！
unsigned int is_key_press(void)
{
	// 如果按下返回 yes_press
	if ((rUTRSTAT0 & (1<<0)))
	{
		// 把获取到的内容清除，否则进入shell后会获取到
		rURXH0 &= 0x00;
		return yes_press;
	}
	// 如果没按下返回 no_press
	else
	{
		return no_press;
	}
}


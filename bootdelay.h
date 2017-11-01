#ifndef _BOOTDELAY_H__
#define _BOOTDELAY_H__

// 倒计时进入shell设置 秒数
#define BOOTDELAYTIMES	8


// 实现功能是 自动倒计时，和按下任意键 进入shell界面
void shell_bootdealy(unsigned int bootdealy_times);

// 检测串口是否有接收到内容，也就是检测是否有任意按键按下！
unsigned int is_key_press(void);

#endif
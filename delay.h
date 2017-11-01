#ifndef __DELAY_H
#define	__DELAY_H


#define S		1000000
#define MS		1000
#define US		1



// 秒级 延时函数
void delays(unsigned int time);
// 毫秒级 延时函数
void delayms(unsigned int time);
// 微秒级 延时函数
void delayus(unsigned int time);

#endif
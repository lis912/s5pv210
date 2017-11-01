#include "stdio.h"
#include "rtc.h"
#include "public.h"


// 设置RTC时钟
void rtc_set_time(const struct rtc_time *p)
{
	// 第一步，打开RTC读写开关
	rRTCCON |= (1<<0);
	
	// 第二步，写RTC时间寄存器
	rBCDYEAR = num_2_bcd(p->year - 2000);
	rBCDMON = num_2_bcd(p->month);
	rBCDDATE = num_2_bcd(p->date);
	rBCDHOUR = num_2_bcd(p->hour);
	rBCDMIN = num_2_bcd(p->minute);
	rBCDSEC = num_2_bcd(p->second);
	rBCDDAY = num_2_bcd(p->day);
	
	// 最后一步，关上RTC的读写开关
	rRTCCON &= ~(1<<0);
}

// 获取RTC时钟
void rtc_get_time(struct rtc_time *p)
{
	// 第一步，打开RTC读写开关
	rRTCCON |= (1<<0);
	
	// 第二步，读RTC时间寄存器
	p->year = bcd_2_num(rBCDYEAR) + 2000;
	p->month = bcd_2_num(rBCDMON);
	p->date = bcd_2_num(rBCDDATE);
	p->hour = bcd_2_num(rBCDHOUR);
	p->minute = bcd_2_num(rBCDMIN);
	p->second = bcd_2_num(rBCDSEC);
	p->day = bcd_2_num(rBCDDAY);
	
	// 最后一步，关上RTC的读写开关
	rRTCCON &= ~(1<<0);
	
	printf("%d-%d-%d  %d-%d-%d day:%d.\n", p->year, p->month, p->date, p->hour, p->minute, p->second, p->day);
}

// RTC设置闹铃中断
void rtc_set_alarm(void)
{
	rALMSEC = num_2_bcd(23);
	rRTCALM |= 1<<0;
	rRTCALM |= 1<<6;
}

// 闹铃中断ISR函数
void isr_rtc_alarm(void)
{
	static int i = 0; 
	printf("rtc alarm, i = %d...", i++);
	
	rINTP |= (1<<1);
}
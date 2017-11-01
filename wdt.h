#ifndef __WDT_H
#define __WDT_H


#define		WTCON		(0xE2700000)
#define		WTDAT		(0xE2700004)
#define		WTCNT		(0xE2700008)
#define 	WTCLRINT	(0xE270000C)

#define 	rWTCON		(*(volatile unsigned int *)WTCON)
#define 	rWTDAT		(*(volatile unsigned int *)WTDAT)
#define 	rWTCNT		(*(volatile unsigned int *)WTCNT)
#define 	rWTCLRINT	(*(volatile unsigned int *)WTCLRINT)

// 初始化WDT使之可以产生中断
void wdt_init_interrupt(void);
// 初始化WDT使之可以产生复位，也就是重新执行main函数
void wdt_init_reset(void);

// wdt的中断处理程序
void isr_wdt(void);


#endif
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

// ��ʼ��WDTʹ֮���Բ����ж�
void wdt_init_interrupt(void);
// ��ʼ��WDTʹ֮���Բ�����λ��Ҳ��������ִ��main����
void wdt_init_reset(void);

// wdt���жϴ������
void isr_wdt(void);


#endif
#ifndef __PWM_H
#define	__PWM_H


#define 	GPD0CON		(0xE02000A0)
#define 	TCFG0		(0xE2500000)
#define 	TCFG1		(0xE2500004)
#define 	CON			(0xE2500008)
#define 	TCNTB2		(0xE2500024)
#define 	TCMPB2		(0xE2500028)
#define 	TCNTO2		(0xE250002C)

#define 	rGPD0CON	(*(volatile unsigned int *)GPD0CON)
#define 	rTCFG0		(*(volatile unsigned int *)TCFG0)
#define 	rTCFG1		(*(volatile unsigned int *)TCFG1)
#define 	rCON		(*(volatile unsigned int *)CON)
#define 	rTCNTB2		(*(volatile unsigned int *)TCNTB2)
#define 	rTCMPB2		(*(volatile unsigned int *)TCMPB2)
#define 	rTCNTO2		(*(volatile unsigned int *)TCNTO2)
//-------------------------------time3----------
#define 	TCNTB3		(0xE2500030)
#define 	TCMPB3		(0xE2500034)
#define 	TCNTO3		(0xE2500038)

#define 	rTCNTB3		(*(volatile unsigned int *)TCNTB3)
#define 	rTCMPB3		(*(volatile unsigned int *)TCMPB3)
#define 	rTCNTO3		(*(volatile unsigned int *)TCNTO3)








// 初始化PWM timer2，使其输出PWM波形：频率是2KHz、duty为50%
void timer2_pwm_init(void);






#endif
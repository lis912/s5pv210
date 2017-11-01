#ifndef __KEY_H
#define	__KEY_H

// 定义操作寄存器的宏
// 定义操作寄存器的宏
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define EXT_INT_0_CON	0xE0200E00
#define EXT_INT_2_CON	0xE0200E08
#define EXT_INT_0_PEND	0xE0200F40
#define EXT_INT_2_PEND	0xE0200F48
#define EXT_INT_0_MASK	0xE0200F00
#define EXT_INT_2_MASK	0xE0200F08


#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)
#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

#define rEXT_INT_0_CON (*(volatile unsigned int *)EXT_INT_0_CON)
#define rEXT_INT_2_CON (*(volatile unsigned int *)EXT_INT_2_CON)
#define rEXT_INT_0_PEND (*(volatile unsigned int *)EXT_INT_0_PEND)
#define rEXT_INT_2_PEND (*(volatile unsigned int *)EXT_INT_2_PEND)
#define rEXT_INT_0_MASK (*(volatile unsigned int *)EXT_INT_0_MASK)
#define rEXT_INT_2_MASK (*(volatile unsigned int *)EXT_INT_2_MASK)

#define FALLING_EDGE_TRIGGE		2
#define RISING_EDGE_TRIGGE		3
#define BOTH_EDGE_TRIGGE		4

// 初始化按键为输入模式
void key_init(void);
// 按键显示键名+延时消抖
void key_polling(void);


// 初始化按键GPIO为中断模式
void key_init_int(void);
// 初始按键相关的化外部中断
void eint_init(void);

// 下面全是按键中断的ISR处理函数
void key_isr_eint2(void);
void key_isr_eint3(void);
void key_isr_eint16171819(void);


#endif
#ifndef __KEY_H
#define	__KEY_H

// ��������Ĵ����ĺ�
// ��������Ĵ����ĺ�
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

// ��ʼ������Ϊ����ģʽ
void key_init(void);
// ������ʾ����+��ʱ����
void key_polling(void);


// ��ʼ������GPIOΪ�ж�ģʽ
void key_init_int(void);
// ��ʼ������صĻ��ⲿ�ж�
void eint_init(void);

// ����ȫ�ǰ����жϵ�ISR������
void key_isr_eint2(void);
void key_isr_eint3(void);
void key_isr_eint16171819(void);


#endif
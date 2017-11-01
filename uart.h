/*
 *  ��s5pv210��鿪������ֻ���� uart0��uart2.
 *	ʵ����ʹ�õ�ʱ��ubootѡ�������� uart2
 *  ���ʵ������ʦ������  uart0
 *	�Ҳ�������������������ʹ��
 */

#ifndef __UART0_UART2_H
#define __UART0_UART2_H


// ���������ó�ʼ����һ������
//define CONFIG_SERIAL0
#define CONFIG_SERIAL2

// �Ĵ�������ַ
#define ELFIN_UART_BASE			0XE2900000

#define ELFIN_UART0_OFFSET		0x0000
#define ELFIN_UART2_OFFSET		0x0800

#if defined(CONFIG_SERIAL0)
#define ELFIN_UART_CONSOLE_BASE (ELFIN_UART_BASE + ELFIN_UART0_OFFSET)
#elif defined(CONFIG_SERIAL2)
#define ELFIN_UART_CONSOLE_BASE (ELFIN_UART_BASE + ELFIN_UART2_OFFSET)
#else
#define ELFIN_UART_CONSOLE_BASE (ELFIN_UART_BASE + ELFIN_UART0_OFFSET)
#endif

#define ELFIN_GPIO_BASE			0xE0200000
#define GPA0CON_OFFSET 			0x000
#define GPA1CON_OFFSET 			0x020



#define ULCON_OFFSET			0x00
#define UCON_OFFSET				0x04
#define UFCON_OFFSET			0x08
#define UMCON_OFFSET			0x0C
#define UTRSTAT_OFFSET			0x10
#define UERSTAT_OFFSET			0x14
#define UFSTAT_OFFSET			0x18
#define UMSTAT_OFFSET			0x1C
#define UTXH_OFFSET				0x20
#define URXH_OFFSET				0x24
#define UBRDIV_OFFSET			0x28
#define UDIVSLOT_OFFSET			0x2C
#define UINTP_OFFSET			0x30
#define UINTSP_OFFSET			0x34
#define UINTM_OFFSET			0x38


#define GPA0CON		(ELFIN_GPIO_BASE + GPA0CON_OFFSET)
#define GPA1CON		(ELFIN_GPIO_BASE + GPA1CON_OFFSET)
#define UCON		(ELFIN_UART_CONSOLE_BASE + UCON_OFFSET)
#define ULCON		(ELFIN_UART_CONSOLE_BASE + ULCON_OFFSET)
#define UMCON		(ELFIN_UART_CONSOLE_BASE + UMCON_OFFSET)
#define UFCON		(ELFIN_UART_CONSOLE_BASE + UFCON_OFFSET)
#define UBRDIV		(ELFIN_UART_CONSOLE_BASE + UBRDIV_OFFSET)
#define UDIVSLOT	(ELFIN_UART_CONSOLE_BASE + UDIVSLOT_OFFSET)
#define UTRSTAT		(ELFIN_UART_CONSOLE_BASE + UTRSTAT_OFFSET)
#define UTXH		(ELFIN_UART_CONSOLE_BASE + UTXH_OFFSET)
#define URXH		(ELFIN_UART_CONSOLE_BASE + URXH_OFFSET)


#define rGPA0CON	(*(volatile unsigned int *)GPA0CON)
#define rUCON0		(*(volatile unsigned int *)UCON)
#define rULCON0		(*(volatile unsigned int *)ULCON)
#define rUMCON0		(*(volatile unsigned int *)UMCON)
#define rUFCON0		(*(volatile unsigned int *)UFCON)
#define rUBRDIV0	(*(volatile unsigned int *)UBRDIV)
#define rUDIVSLOT0	(*(volatile unsigned int *)UDIVSLOT)
#define rUTRSTAT0	(*(volatile unsigned int *)UTRSTAT)
#define rUTXH0		(*(volatile unsigned int *)UTXH)
#define rURXH0		(*(volatile unsigned int *)URXH)

// ��������
// ���ڳ�ʼ������
void uart_init(void);

// ���ڷ��ͳ��򣬷���һ���ֽ�
//void putc(char c);

// ���ڽ��ճ�����ѯ��ʽ������һ���ֽ�
//char getc(void);

// �����������������󱨴�previous declaration of 'putc' was here �ƺ��ǳ�ͻ��

// ��stdio���һ���ַ���p
void puts(const char *p);	// ������һ���ַ�������ָ�� char*p = "aston" 

// ��stdio����һ���ַ���
// ����ֵָ�򴫽�����������׵�ַ�ģ�Ŀ����ʵ�ֺ����ļ�������
char* gets(char *p);

//	******** ���º�������shell�����ʹ�� *************************
// ���ڷ��ͳ��򣬷���һ���ֽ�
void shell_putc(char c);

#endif
/*
 *  在s5pv210这块开发板上只接了 uart0，uart2.
 *	实际在使用的时候，uboot选择启动了 uart2
 *  裸机实验中老师启用了  uart0
 *	我采用了条件编译来进行使用
 */

#ifndef __UART0_UART2_H
#define __UART0_UART2_H


// 在这里配置初始化哪一个串口
//define CONFIG_SERIAL0
#define CONFIG_SERIAL2

// 寄存器基地址
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

// 函数声明
// 串口初始化程序
void uart_init(void);

// 串口发送程序，发送一个字节
//void putc(char c);

// 串口接收程序，轮询方式，接收一个字节
//char getc(void);

// 以上两个函数声明后报错：previous declaration of 'putc' was here 似乎是冲突了

// 从stdio输出一个字符串p
void puts(const char *p);	// 参数是一个字符串常量指针 char*p = "aston" 

// 从stdio输入一个字符串
// 返回值指向传进来的数组的首地址的，目的是实现函数的级联调用
char* gets(char *p);

//	******** 以下函数仅在shell裸机中使用 *************************
// 串口发送程序，发送一个字节
void shell_putc(char c);

#endif
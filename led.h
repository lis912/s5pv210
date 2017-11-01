#ifndef __LED_H
#define __LED_H

// for cmd_tbl_t *cmdtp to include it
#include "g_cmd.h"

#define GPJ0CON			0xE0200240
#define GPJ0DAT			0xE0200244
#define GPD0CON_2		0xE02000A0
#define GPD0DAT			0xE02000A4

#define rGPJ0CON		*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT		*((volatile unsigned int *)GPJ0DAT)
#define rGPD0CON_2		*((volatile unsigned int *)GPD0CON_2)
#define rGPD0DAT		*((volatile unsigned int *)GPD0DAT)



// led初始化
void led_init(void);

// 该函数要实现led闪烁效果
void led_blink(void);
// 花式闪灯
void led_figure (void);
// 跑马灯
void led_paomadeng(void);
// 点亮D25
void led_d25on(void);
// 全部点亮
void led_all_on(void);
// 全部熄灭
void led_all_off(void);
// 指定点亮某一颗led,不管led灯原来是什么状态
void led_select(int i);


int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);


#endif
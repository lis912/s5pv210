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



// led��ʼ��
void led_init(void);

// �ú���Ҫʵ��led��˸Ч��
void led_blink(void);
// ��ʽ����
void led_figure (void);
// �����
void led_paomadeng(void);
// ����D25
void led_d25on(void);
// ȫ������
void led_all_on(void);
// ȫ��Ϩ��
void led_all_off(void);
// ָ������ĳһ��led,����led��ԭ����ʲô״̬
void led_select(int i);


int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);


#endif
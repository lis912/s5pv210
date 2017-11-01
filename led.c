#include "main.h"





// led��ʼ��
void led_init(void)
{
	// led��ʼ����Ҳ���ǰ�GPJ0CON������Ϊ���ģʽ
	rGPJ0CON = 0x11111111;
	
	// ����һ��D25����Ϊ���ģʽ
	rGPD0CON_2 &= ~(0xf<<4);
	rGPD0CON_2 |= (0x1<<4);
	
}

// ����D25����͵�ƽ������
void led_d25on(void)
{
	rGPD0DAT |= (0<<1);
}

// ȫ������
void led_all_on(void)
{
	rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
	rGPD0DAT |= (0<<1);
}

// ȫ��Ϩ��
void led_all_off(void)
{
	rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
	rGPD0DAT |= (1<<1);
}

/*
// ָ������ĳһ��led,����led��ԭ����ʲô״̬
void led_select(int i)
{	
	switch (i)
	{
		case 1:
		rGPJ0DAT = ((0<<3);
		break;
		
		case 2:
		rGPJ0DAT = ((0<<4);
		break;
		
		case 3:
		rGPJ0DAT = ((0<<5);
		break;
		
		case 4:
		rGPD0DAT |= (0<<1);
		break;
		
		default:
		printf("usage: The argument limits must 1~4 ");
		break;
	}
}
*/

// �ú���Ҫʵ��led��˸Ч��
void led_blink(void)
{
	// led��ʼ����Ҳ���ǰ�GPJ0CON������Ϊ���ģʽ
	//volatile unsigned int *p = (unsigned int *)GPJ0CON;
	//volatile unsigned int *p1 = (unsigned int *)GPJ0DAT;
	rGPJ0CON = 0x11111111;
	
	while (1)
	{
		// led��
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
		rGPD0DAT |= (0<<1);
		// ��ʱ
		delays(1);
		// led��
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
		rGPD0DAT |= (1<<1);
		// ��ʱ
		delays(1);
	}
}


// ��ʽ����
void led_figure (void)
{
	while(1)
	{
		unsigned int i;
		// ��8�������ѭ��
		for(i=0; i<8; i++)
		{
			rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
			delays(100);
		}
		// ȫ��ȫ��8��
		for (i=0; i<8; i++)
		{
			rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
			delays(100);
			rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
			delays(100);
		}
	}
	 
}

// �����
void led_paomadeng(void)
{
	while(1)
	{
		rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
		delays(100);
		rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
		delays(100);
		rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
		delays(100);
	}
}	



int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc == 2)
	{
		if (!strcmp(argv[1], "on"))
		{
			led_all_on();
		}
		else if (!strcmp(argv[1], "off"))
		{
			led_all_off();
		}
		else
		{
			printf ("Usage:\n%s\n", cmdtp->usage);
			return 1;
		}
			
	}

	return 0;
}


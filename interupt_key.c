#include "stdio.h"
#include "key.h"
#include "led.h"


// ��ʼ������GPIOΪ�ж�ģʽ
void key_init_int(void)
{
	// ����GPIOΪ�ж�ģʽ
	rGPH0CON &= ~(0xFF<<8);
	rGPH0CON |= (0xFF<<8);
	rGPH2CON &= ~(0xFFFF<<0);
	rGPH2CON |= (0xFFFF<<0);
}

// ��ʼ������صĻ��ⲿ�ж�
void eint_init(void)
{
	key_init_int();
	
	// ���ð����жϴ�����ʽ��ͳһΪ�½��ش���,Ҳ���ǰ��µ�ʱ��
	rEXT_INT_0_CON &= ~((7<<8) | (7<<12));
	rEXT_INT_0_CON |= ((FALLING_EDGE_TRIGGE<<8) | (FALLING_EDGE_TRIGGE<<12));
	rEXT_INT_2_CON &= ~(0xffff<<0);
	rEXT_INT_2_CON |= ((FALLING_EDGE_TRIGGE<<0)|(FALLING_EDGE_TRIGGE<<4)|(FALLING_EDGE_TRIGGE<<8)|(FALLING_EDGE_TRIGGE<<12));
	
	// ���жϹ���λ,�˼Ĵ������жϱ�־λ��1��ʾ�жϷ�����0��ʾ�޷�������ʼ��Ϊ0
	rEXT_INT_0_PEND &= ~(1<<2 | 1<<3);
	rEXT_INT_2_PEND &= ~(0x0f<<0);
	
	// ʹ��/��ֹ �ⲿ�ж�
	rEXT_INT_0_MASK &= ~(3<<2);
	rEXT_INT_2_MASK &= ~(0x0f<<0);
}

// ����ȫ�ǰ����жϵ�ISR������
void key_isr_eint2(void)
{	
	// �ֶ������д1�����
	rEXT_INT_0_PEND |= (1<<2);
	
	printf("eint2 key LEFT.\n");
}

void key_isr_eint3(void)
{
	rEXT_INT_0_PEND |= (1<<3);
	
	printf("eint3 key DOWN.\n");
}

void key_isr_eint16171819(void)
{
	if (rEXT_INT_2_PEND & (1<<0))
	{
		printf("eint16 key UP.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<1))
	{
		printf("eint17 key RIGHT.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<2))
	{
		printf("eint18 key BACK.\n");
	}
	
	if (rEXT_INT_2_PEND & (1<<3))
	{
		printf("eint19 key MENU.\n");
	}
	
	rEXT_INT_2_PEND |= (0x0f<<0);
}




















#include "stdio.h"
#include "key.h"

// ��ʼ������
void key_init(void)
{
	// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	rGPH0CON &= ~(0xFF<<8);
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xFFFF<<0);
}

void delay20ms(void)
{
	// ���������������ʱ20ms
	// ��Ϊ��������������������ص㲻�����Ҫ���������ǽ�ѧ
	// �����������������ֻ�������Եģ���û��ʵ��
	// ������з����Ǿ�Ҫ��ʱ����ĵ��Գ���ʱ20ms�ĳ���
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}

// ������ʾ����+��ʱ����
void key_polling(void)
{
	// ���Σ�����ȥ����ÿ��GPIO��ֵ���ж���ֵΪ1����0.���Ϊ1�򰴼����£�Ϊ0����
	
	// ��ѯ����˼���Ƿ���ѭ���ж����ް��������ܶ�ʱ��
	while (1)
	{
		// ��Ӧ�������ϱ���LEFT���Ǹ�����
		if (rGPH0DAT & (1<<2))
		{
			// Ϊ1��˵��û�а���
		}
		else
		{
			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH0DAT & (1<<2)))
			{
				// Ϊ0��˵���а���
				printf("key left.\n");
			}
		}
		
		
		// ��Ӧ�������ϱ���DOWN���Ǹ�����
		if (rGPH0DAT & (1<<3))
		{
			// Ϊ1��˵��û�а���
		}
		else
		{
			// Ϊ0��˵���а���
			printf("key down.\n");
		}
		
		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<0))
		{
			// Ϊ1��˵��û�а���
			//led_off();
		}
		else
		{
			// Ϊ0��˵���а���
			printf("key UP.\n");
		}
		
		if (rGPH2DAT & (1<<1))
		{
			
		}
		else
		{
			printf("key RIGHT.\n");
		}
		
		if (rGPH2DAT & (1<<2))
		{
			
		}
		else
		{
			printf("key BACK.\n");
		}
		
		if (rGPH2DAT & (1<<3))
		{
			
		}
		else
		{
			printf("key MENU.\n");
		}
	}
}


























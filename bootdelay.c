#include "main.h"

unsigned int yes_press = 1;
unsigned int no_press = 0;


// ʵ�ֹ���: �Զ�����ʱ���Ͱ�������� ����shell����
void shell_bootdealy(unsigned int count_down)
{
	printf("Press any key to enter shell: ");
	// �߼����ͣ������밴��=�� && ����ʱ����0=�� 	while���� 
	while ((!(is_key_press() == yes_press)) && (!(count_down == 0)))
	{
		printf("%d", count_down);		// ��ӡ��ǰ����ʱ
		shell_putc('\b');				// �ѹ���˵�ǰһ���ַ���
		delays(1);						// ��ʱ1s
		--count_down;					// ����ʱ--
	}
}

// ��⴮���Ƿ��н��յ����ݣ�Ҳ���Ǽ���Ƿ������ⰴ�����£�
unsigned int is_key_press(void)
{
	// ������·��� yes_press
	if ((rUTRSTAT0 & (1<<0)))
	{
		// �ѻ�ȡ��������������������shell����ȡ��
		rURXH0 &= 0x00;
		return yes_press;
	}
	// ���û���·��� no_press
	else
	{
		return no_press;
	}
}


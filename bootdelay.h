#ifndef _BOOTDELAY_H__
#define _BOOTDELAY_H__

// ����ʱ����shell���� ����
#define BOOTDELAYTIMES	8


// ʵ�ֹ����� �Զ�����ʱ���Ͱ�������� ����shell����
void shell_bootdealy(unsigned int bootdealy_times);

// ��⴮���Ƿ��н��յ����ݣ�Ҳ���Ǽ���Ƿ������ⰴ�����£�
unsigned int is_key_press(void);

#endif
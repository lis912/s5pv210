#include "main.h"


// ���尴���жϺ����"key.h"
#define KEY_LEFT					NUM_EINT2		// LEFT 
#define KEY_DOWN					NUM_EINT3		// DOWN
#define KEY_UP_BACK_RIGHT_MENU		NUM_EINT16_31	// ����16���ж�


// ����ṹ����������
extern cmd_tbl_t g_cmd[CFG_CMDCNT];
extern int g_cmd_cnt;		// ���������

// ���Դ�ӡ����
void test(int a);

// �ⲿ�жϰ�
void external_interuper_enable(void)
{
	// ���жϴ�����isr���ⲿ�жϣ���ʹ��
	intc_setvectaddr(KEY_LEFT, key_isr_eint2);
	intc_setvectaddr(KEY_DOWN, key_isr_eint3);
	intc_setvectaddr(KEY_UP_BACK_RIGHT_MENU, key_isr_eint16171819);
	//intc_setvectaddr(NUM_WDT, isr_wdt);
	//intc_setvectaddr(NUM_RTC_ALARM, isr_rtc_alarm);
}



int main(void)
{
	struct rtc_time haha;
	char cmdbuf[256] = {0};
	char *argv[16 + 1];	/* NULL terminated	*/	
	cmd_tbl_t *cmdtp;
	char *token;			/* start of token in cmdbuf	*/
	char *sep;				/* end of token (separator) in cmdbuf */
	char finaltoken[256];
	int argc, inquotes;
	int repeatable = 1;
	int rc = 0;
	int flag = 0;
	
	// ��ʼ����Ӳ��ģ��
	init_modules();
	
	// �ⲿ�ж�ʹ��
	external_interuper_enable();
	
	// ��ȡRTCʱ��������Ժ���
	//rtc_get_time(&haha);
	
	
	// ��ʱ����shell
	shell_bootdealy(BOOTDELAYTIMES);
	
	// ��ʼ��shell����
	init_shell_env();
	
	// shellͷ��־
	printf("\nx210 shell:\n");
	
	while (1)
	{
		// ģ���û�����־
		puts("lishichang@ ");
		memset(cmdbuf, 0, sizeof(cmdbuf));
		gets(cmdbuf);
		
		// �س�=����
		if (*cmdbuf == '\0')
			continue;
		
		// ��������������
		argc = parse_line(cmdbuf, argv);
		
		// Ѱ��ƥ������
		if ((cmdtp = find_cmd(argv[0])) == NULL) 
		{
			printf ("Unknown command '%s' - try 'help'\n", argv[0]);
			rc = -1;	/* give up after bad command */
			continue;
		}
		
		// ִ������
		if ((cmdtp->cmd) (cmdtp, flag, argc, argv) != 0) 
		{
			rc = -1;
		}
		
	}
	
	
	return 0;

}




void test(int a)
{
	printf("*** %d ***\n", a);
	return;
}
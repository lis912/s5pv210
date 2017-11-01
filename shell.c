#include "main.h"

// ȫ�ֱ������������������ļ��޷�ʹ��
extern cmd_tbl_t g_cmd[10];
extern int g_cmd_cnt;		// ʵ�ʶ��������������ʼֵ


// ��ʼ�����е�Ӳ����������ģ��
void init_modules(void)
{
	// ���ڳ�ʼ����
	uart_init();
	// ģ��ת��ADC����
	//adc_test();
	// �жϳ�ʼ����
	system_init_exception();	
	// �ⲿ�жϳ�ʼ��
	eint_init();
	//wdt_init_interrupt();
	//rtc_set_alarm();
	// led��ʼ��
	led_init();
}


// 2. ��������
int parse_line (char *line, char *argv[])
{
	int nargs = 0;

#ifdef DEBUG_PARSER
	printf ("parse_line: \"%s\"\n", line);
#endif
	while (nargs < CFG_MAXARGS) {

		/* skip any white space */
		while ((*line == ' ') || (*line == '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		argv[nargs++] = line;	/* begin of argument string	*/

		/* find end of string */
		while (*line && (*line != ' ') && (*line != '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
		printf ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		*line++ = '\0';		/* terminate current arg	 */
	}

	printf ("** Too many args (max. %d) **\n", CFG_MAXARGS);

#ifdef DEBUG_PARSER
	printf ("parse_line: nargs=%d\n", nargs);
#endif
	return (nargs);
}



cmd_tbl_t *find_cmd (const char *cmd)
{
	// �������
		int i;
		for (i=0; i<g_cmd_cnt; i++)
		{
			// cmd[0]���Ǵ������еĵ�һ���ַ�����Ҳ����������
			if (!strcmp(cmd, g_cmd[i].name))
			{
				// ��ȣ��ҵ�����������ȥִ�������������Ӧ�Ķ�����
				return &g_cmd[i];
				
				break;
			}
		}				
		
		return NULL;
}




// ��ʼshell����
void init_shell_env(void)
{
	// 1. ��ʼ��shell��������ϵ
	init_cmd_set();
}

// ��ʼ�������б�
void init_cmd_set(void)
{		
	// ��ȫ�����㣬�����g_cmdset�����ǣ�
	memset((char *)g_cmd, 0, sizeof(g_cmd));
	
	cmd_reg("print", 5, do_printenv, "print argv too long...");
	cmd_reg("setenv", 2, do_setenv, "setenv argv too long...");
	cmd_reg("led", 3, do_led, "led  parameter is on/off.");
	
}




#include "main.h"

// 全局变量声明，否则其他文件无法使用
extern cmd_tbl_t g_cmd[10];
extern int g_cmd_cnt;		// 实际定义的命令数量初始值


// 初始化所有的硬件外设和软件模块
void init_modules(void)
{
	// 串口初始化化
	uart_init();
	// 模数转换ADC外设
	//adc_test();
	// 中断初始化化
	system_init_exception();	
	// 外部中断初始化
	eint_init();
	//wdt_init_interrupt();
	//rtc_set_alarm();
	// led初始化
	led_init();
}


// 2. 解析命令
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
	// 解析命令：
		int i;
		for (i=0; i<g_cmd_cnt; i++)
		{
			// cmd[0]就是次命令中的第一个字符串，也就是主命令
			if (!strcmp(cmd, g_cmd[i].name))
			{
				// 相等，找到了这个命令，就去执行这个命令所对应的动作。
				return &g_cmd[i];
				
				break;
			}
		}				
		
		return NULL;
}




// 初始shell环境
void init_shell_env(void)
{
	// 1. 初始化shell的命令体系
	init_cmd_set();
}

// 初始化命令列表
void init_cmd_set(void)
{		
	// 先全部清零，这里的g_cmdset类型是：
	memset((char *)g_cmd, 0, sizeof(g_cmd));
	
	cmd_reg("print", 5, do_printenv, "print argv too long...");
	cmd_reg("setenv", 2, do_setenv, "setenv argv too long...");
	cmd_reg("led", 3, do_led, "led  parameter is on/off.");
	
}




#include "main.h"


// 定义按键中断号详见"key.h"
#define KEY_LEFT					NUM_EINT2		// LEFT 
#define KEY_DOWN					NUM_EINT3		// DOWN
#define KEY_UP_BACK_RIGHT_MENU		NUM_EINT16_31	// 共用16号中断


// 命令结构体数组声明
extern cmd_tbl_t g_cmd[CFG_CMDCNT];
extern int g_cmd_cnt;		// 命令计数器

// 调试打印函数
void test(int a);

// 外部中断绑定
void external_interuper_enable(void)
{
	// 绑定中断处理函数isr到外部中断，并使能
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
	
	// 初始化软硬件模块
	init_modules();
	
	// 外部中断使能
	external_interuper_enable();
	
	// 获取RTC时钟输出调试函数
	//rtc_get_time(&haha);
	
	
	// 延时进入shell
	shell_bootdealy(BOOTDELAYTIMES);
	
	// 初始化shell环境
	init_shell_env();
	
	// shell头标志
	printf("\nx210 shell:\n");
	
	while (1)
	{
		// 模拟用户名标志
		puts("lishichang@ ");
		memset(cmdbuf, 0, sizeof(cmdbuf));
		gets(cmdbuf);
		
		// 回车=换行
		if (*cmdbuf == '\0')
			continue;
		
		// 解析命令行输入
		argc = parse_line(cmdbuf, argv);
		
		// 寻找匹配命令
		if ((cmdtp = find_cmd(argv[0])) == NULL) 
		{
			printf ("Unknown command '%s' - try 'help'\n", argv[0]);
			rc = -1;	/* give up after bad command */
			continue;
		}
		
		// 执行命令
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
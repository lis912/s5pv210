#include "main.h"

/* 所有的命令在 cmd_reg 函数下注册到全局变量g_cmd下 */

cmd_tbl_t g_cmd[CFG_CMDCNT];
int g_cmd_cnt = 0;		// 实际定义的命令数量初始值





// 命令注册函数：
void cmd_reg(char* name, int maxargs, int (*cmd)(struct cmd_tbl_s *, int, int, char *[]), char *usage)
{
	g_cmd[g_cmd_cnt].name = name;
	g_cmd[g_cmd_cnt].maxargs = maxargs;
	g_cmd[g_cmd_cnt].cmd = cmd;
	g_cmd[g_cmd_cnt].usage = usage;
	
	g_cmd_cnt++;
}






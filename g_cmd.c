#include "main.h"

/* ���е������� cmd_reg ������ע�ᵽȫ�ֱ���g_cmd�� */

cmd_tbl_t g_cmd[CFG_CMDCNT];
int g_cmd_cnt = 0;		// ʵ�ʶ��������������ʼֵ





// ����ע�ắ����
void cmd_reg(char* name, int maxargs, int (*cmd)(struct cmd_tbl_s *, int, int, char *[]), char *usage)
{
	g_cmd[g_cmd_cnt].name = name;
	g_cmd[g_cmd_cnt].maxargs = maxargs;
	g_cmd[g_cmd_cnt].cmd = cmd;
	g_cmd[g_cmd_cnt].usage = usage;
	
	g_cmd_cnt++;
}






#ifndef _G_CMD_H__
#define _G_CMD_H__

// ���������Ĳ������� 
#define CFG_MAXARGS		16		/* max number of command args	*/ 
#define CFG_CMDCNT		25





// �������ݽṹģ�� 
struct cmd_tbl_s 
{
	char		*name;		/* Command Name			*/
	int			maxargs;	/* maximum number of arguments	*/
	int		(*cmd)(struct cmd_tbl_s *, int, int, char *[]);
	char		*usage;		/* Usage message	(short)	*/
};
typedef struct cmd_tbl_s	cmd_tbl_t;


// ע��һ��ȫ������
void cmd_reg(char* name, int maxargs, int (*cmd)(struct cmd_tbl_s *, int, int, char *[]), char *usage);
void init_cmd_set(void);






#endif

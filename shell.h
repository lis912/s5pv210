#ifndef _SHELL_H__
#define _SHELL_H__

// �궨��
#define MAX_LINE_LENGTH		256			// �����г��ȣ�����ܳ����������



// ��ʼ�����е�Ӳ����������ģ��
void init_modules(void);

// ��ʼshell����
// void init_shell_env(void);


void init_shell_env(void);

// 2. ��������
int parse_line (char *line, char *argv[]);

// 3. Ѱ������
cmd_tbl_t *find_cmd (const char *cmd);

#endif
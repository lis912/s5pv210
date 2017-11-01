#ifndef _SHELL_H__
#define _SHELL_H__

// 宏定义
#define MAX_LINE_LENGTH		256			// 命令行长度，命令不能超过这个长度



// 初始化所有的硬件外设和软件模块
void init_modules(void);

// 初始shell环境
// void init_shell_env(void);


void init_shell_env(void);

// 2. 解析命令
int parse_line (char *line, char *argv[]);

// 3. 寻找命令
cmd_tbl_t *find_cmd (const char *cmd);

#endif
#include "main.h"


// 环境变量数据结构,注意"aa="这里的"="两边不加空格，不然处理算法就失效了
char env_str[256] = 
{
	"bootdealy="	"8" 		"\0"
	"uart_out="		"2" 		"\0"
	"sdram="		"512MB" 		"\0"
	"\0"
	// 系统下最后尾部默认会再加一个 '\0'.
	// 但是在uboot中没有系统，需要自己手动加一个 '\0'，否则无法识别是否最后的结尾
};


/**
 *	描述：比对参数字符串是否存在于环境变量字符串中 
 *	参数：
 *		argv	待比对参数字符串
 *		n		环境变量字符串的指针偏移量  
 *		env		环境变量字符串数组的地址
 */
int env_match(char *argv, int n, const char *env)
{
	//printf("**n = %d.\n", n);
	while (*argv == *( env+(n++) ))
	{
		//printf("n = %d.\n", n);
		if (*argv++ == '=')
			return(n);
	}
		
	if (*argv == '\0' && *( env+(n-1) ) == '=')
		return(n);
	return(-1);
}





// 打印输出全部的环境变量，参数 p 输入环境变量字符串首地址
void print_all_env(void)
{
	int i, j ,k;
	char *p = env_str;
	
	for(i=0; *(p+i)!= '\0'; i=j+1)
	{
		for(j=i; *(p+j)!= '\0'; j++);		
		for(k=i; k<j; k++)
		{
			// 输出样式：在 '=' 前面加一 空格
			if (*(p+k) == '=')
				printf(" ");
			
			printf("%c", *(p+k));
			
			// 输出样式：在 '=' 后面加一 空格
			if (*(p+k) == '=')
				printf(" ");			
		}
		printf("\n");		
	} 
}


// 输出参数对应的环境变量
int put_env(int argc, char *argv[])
{
	int i;		// 首层for使用
	char *p = env_str;
	
	// 参数大于1的情况，就是单独打印参数所对应的环境变量
	for (i=1; i<argc; ++i)
	{	
		char *name = argv[i];
		int i, j ,k;
	
	
		for(i=0; *(p+i)!= '\0'; i=j+1)
		{
			for(j=i; *(p+j)!= '\0'; j++);
			// 比对参数和环境变量里有没有对应的,返回'='后的指针偏移量k
			k = env_match(name, i, p);
			if (k < 0) 
			{
				continue;
			}
			printf("%s = ", name);
			while (k < j)
				//printf("%c", env_str[k++]);
				printf("%c", *( p+(k++) ) );
			printf("\n");
			break;
		} 
		
		// 没找到输出错误信息
		if (k < 0) 
		{
			printf ("## Error: \"%s\" not defined\n", name);
		}	
	}
	
	
	return 0;
}




// 输出环境变量
int do_printenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc > (cmdtp->maxargs))
	{
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}
	// 如果没有附带参数，则全部打印
	if (argc == 1)
	{
		print_all_env();
		return 0;
	}
	
	// 否则输出指定参数环境变量
	put_env(argc, argv);
	return 0;
	
}


// 设置环境变量命令
int do_setenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int   i, len, oldval;
	int   console = -1;
	char *env, *nxt = NULL;
	char *name;
	oldval = -1;	
	// env_get_addr(0)，返回的是整个环境变量字符串的首地址
	char *env_data = &env_str[0];

	
	if (argc < 2) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	// 假如 env_data=NULL=0，取反等于1，说明地址不准确 返回！
	if (!env_data)	/* need copy in RAM */
		return 1;
	// 把参数aa保存到name这里
	name = argv[1];
	
	/**
	uchar *env, *nxt = NULL;
	env : 		char指针
	env_data: 	环境变量首地址

	*env 等价于  *env != '\0' \0
	nxt:		单个环境变量字符串移动指针，退出时候指向一个字符串尾部  \0
	oldval：	返回单个字符串'='后的指针偏移量k		
	*/
	for (env=env_data; *env; env=nxt+1) 
	{
		for (nxt=env; *nxt; ++nxt)
			;
		if ((oldval = env_match((char *)name, env-env_data, env_data)) >= 0)
			break;
	}
	
	/**
		经过测试，如下代码块的功能是，将待替换的原字符串全部

	*/
		// 如果nxt指向的是整个环境变量字符串的尾部，那么*++nxt == '\0' true
		if (*++nxt == '\0') 
		{
			
			// env一般会指向最后一个字符串的第一个字符 env > env_data true
			// 此时把指针退后一格，在最后添加环境变量的末尾标志 *++env = '\0'
			// 就达到的删除该字符串的目的
			if (env > env_data)
			{
				env--;
			} 
			else 
			{
				*env = '\0';
			}
		} 
		// 如果不是在尾部，而是在中间的某一个字符串就走这里
		else 
		{
			for (;;)
			{
				// 将*env='\0', 直到*env == '\0'
				*env = *nxt++;
				if ((*env == '\0') && (*nxt == '\0'))
					break;
				++env;
			}
		}
		*++env = '\0';
		
	
	// 添加新的name
	while ((*env = *name++) != '\0')
		env++;
	
	for (i=2; i<argc; ++i) 
	{
		// 将参数值赋值给val
		char *val = argv[i];

		// for第一次进来 必定i==2，则给name后添加 '='
		// 之后的拷贝i==2不成立，参数之间用 ' '隔开
		*env = (i==2) ? '=' : ' ';
		// 拷贝每一个 argv
		while ((*++env = *val++) != '\0')
			;
	}

	/* end is marked with double '\0' */
	*++env = '\0';


	
	return 0;
}



// 获取环境变量的值
char *getenv (char *name)
{
	char *p = env_str;
	int i, j ,k;
	
	
	for(i=0; *(p+i)!= '\0'; i=j+1)
	{
		for(j=i; *(p+j)!= '\0'; j++);
		// 比对参数和环境变量里有没有对应的,返回'='后的指针偏移量k
		if ((k = env_match(name, i, p)) < 0) 
			continue;
			
		return (p+k);
	} 
		
	// 没找到输出错误信息
	if (k < 0) 
	{
		printf ("## Error: \"%s\" get fail! \n", name);
	}	
	
	return NULL;
}



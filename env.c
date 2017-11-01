#include "main.h"


// �����������ݽṹ,ע��"aa="�����"="���߲��ӿո񣬲�Ȼ�����㷨��ʧЧ��
char env_str[256] = 
{
	"bootdealy="	"8" 		"\0"
	"uart_out="		"2" 		"\0"
	"sdram="		"512MB" 		"\0"
	"\0"
	// ϵͳ�����β��Ĭ�ϻ��ټ�һ�� '\0'.
	// ������uboot��û��ϵͳ����Ҫ�Լ��ֶ���һ�� '\0'�������޷�ʶ���Ƿ����Ľ�β
};


/**
 *	�������ȶԲ����ַ����Ƿ�����ڻ��������ַ����� 
 *	������
 *		argv	���ȶԲ����ַ���
 *		n		���������ַ�����ָ��ƫ����  
 *		env		���������ַ�������ĵ�ַ
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





// ��ӡ���ȫ���Ļ������������� p ���뻷�������ַ����׵�ַ
void print_all_env(void)
{
	int i, j ,k;
	char *p = env_str;
	
	for(i=0; *(p+i)!= '\0'; i=j+1)
	{
		for(j=i; *(p+j)!= '\0'; j++);		
		for(k=i; k<j; k++)
		{
			// �����ʽ���� '=' ǰ���һ �ո�
			if (*(p+k) == '=')
				printf(" ");
			
			printf("%c", *(p+k));
			
			// �����ʽ���� '=' �����һ �ո�
			if (*(p+k) == '=')
				printf(" ");			
		}
		printf("\n");		
	} 
}


// ���������Ӧ�Ļ�������
int put_env(int argc, char *argv[])
{
	int i;		// �ײ�forʹ��
	char *p = env_str;
	
	// ��������1����������ǵ�����ӡ��������Ӧ�Ļ�������
	for (i=1; i<argc; ++i)
	{	
		char *name = argv[i];
		int i, j ,k;
	
	
		for(i=0; *(p+i)!= '\0'; i=j+1)
		{
			for(j=i; *(p+j)!= '\0'; j++);
			// �ȶԲ����ͻ�����������û�ж�Ӧ��,����'='���ָ��ƫ����k
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
		
		// û�ҵ����������Ϣ
		if (k < 0) 
		{
			printf ("## Error: \"%s\" not defined\n", name);
		}	
	}
	
	
	return 0;
}




// �����������
int do_printenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (argc > (cmdtp->maxargs))
	{
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}
	// ���û�и�����������ȫ����ӡ
	if (argc == 1)
	{
		print_all_env();
		return 0;
	}
	
	// �������ָ��������������
	put_env(argc, argv);
	return 0;
	
}


// ���û�����������
int do_setenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int   i, len, oldval;
	int   console = -1;
	char *env, *nxt = NULL;
	char *name;
	oldval = -1;	
	// env_get_addr(0)�����ص����������������ַ������׵�ַ
	char *env_data = &env_str[0];

	
	if (argc < 2) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	// ���� env_data=NULL=0��ȡ������1��˵����ַ��׼ȷ ���أ�
	if (!env_data)	/* need copy in RAM */
		return 1;
	// �Ѳ���aa���浽name����
	name = argv[1];
	
	/**
	uchar *env, *nxt = NULL;
	env : 		charָ��
	env_data: 	���������׵�ַ

	*env �ȼ���  *env != '\0' \0
	nxt:		�������������ַ����ƶ�ָ�룬�˳�ʱ��ָ��һ���ַ���β��  \0
	oldval��	���ص����ַ���'='���ָ��ƫ����k		
	*/
	for (env=env_data; *env; env=nxt+1) 
	{
		for (nxt=env; *nxt; ++nxt)
			;
		if ((oldval = env_match((char *)name, env-env_data, env_data)) >= 0)
			break;
	}
	
	/**
		�������ԣ����´����Ĺ����ǣ������滻��ԭ�ַ���ȫ��

	*/
		// ���nxtָ������������������ַ�����β������ô*++nxt == '\0' true
		if (*++nxt == '\0') 
		{
			
			// envһ���ָ�����һ���ַ����ĵ�һ���ַ� env > env_data true
			// ��ʱ��ָ���˺�һ���������ӻ���������ĩβ��־ *++env = '\0'
			// �ʹﵽ��ɾ�����ַ�����Ŀ��
			if (env > env_data)
			{
				env--;
			} 
			else 
			{
				*env = '\0';
			}
		} 
		// ���������β�����������м��ĳһ���ַ�����������
		else 
		{
			for (;;)
			{
				// ��*env='\0', ֱ��*env == '\0'
				*env = *nxt++;
				if ((*env == '\0') && (*nxt == '\0'))
					break;
				++env;
			}
		}
		*++env = '\0';
		
	
	// ����µ�name
	while ((*env = *name++) != '\0')
		env++;
	
	for (i=2; i<argc; ++i) 
	{
		// ������ֵ��ֵ��val
		char *val = argv[i];

		// for��һ�ν��� �ض�i==2�����name����� '='
		// ֮��Ŀ���i==2������������֮���� ' '����
		*env = (i==2) ? '=' : ' ';
		// ����ÿһ�� argv
		while ((*++env = *val++) != '\0')
			;
	}

	/* end is marked with double '\0' */
	*++env = '\0';


	
	return 0;
}



// ��ȡ����������ֵ
char *getenv (char *name)
{
	char *p = env_str;
	int i, j ,k;
	
	
	for(i=0; *(p+i)!= '\0'; i=j+1)
	{
		for(j=i; *(p+j)!= '\0'; j++);
		// �ȶԲ����ͻ�����������û�ж�Ӧ��,����'='���ָ��ƫ����k
		if ((k = env_match(name, i, p)) < 0) 
			continue;
			
		return (p+k);
	} 
		
	// û�ҵ����������Ϣ
	if (k < 0) 
	{
		printf ("## Error: \"%s\" get fail! \n", name);
	}	
	
	return NULL;
}



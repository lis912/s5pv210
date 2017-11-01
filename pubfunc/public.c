#include "stdio.h"
#include "public.h"

/*
 *	���������ļ��� �ռ�������µĹ��ܺ����������ַ����Ĵ�����	
 *
 *
 */




// �ַ�������ת��Ϊ����������
unsigned int str_to_int(const char* str)
{
    int i=0, num=0;   
  
    for(i=0; str[i]!='\0'; i++)
	{  	
		//��֤�������ַ���
        if( (str[i] >= '0') && (str[i] <= '9') )	
			// ����ASCII��Ĵ�λʵ��
			num = num*10 + (str[i]-'0');
		else
		{
			printf(" parame error! .\n ");
			return 0;
		}
    }  
     
    return num;  
}

// ���������ʱ��bug ��������0 �޷�����ַ�����"0",��Ȼ���bug�Ѿ�˳�������
void int_to_str(int n, char *str)
{
    char buf[10] = "";
    int i = 0;
    int len = 0;
    int temp = n < 0 ? -n: n;  // tempΪn�ľ���ֵ
  
	// ���������飬str�������ڴ�ռ�
    if (str == NULL)
    {
        return;
    }
	// ��0��ͷ�����Ĵ���취������int 098����ʵ��������һ�����Ϸ����з�������
	// ��������Ϊ�б�Ҫ���϶� 0 �Ĵ�����
	if (n == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return;
	}
	
	 //��temp��ÿһλ�ϵ�������buf
    while(temp)
    {
        buf[i++] = (temp % 10) + '0'; 
        temp = temp / 10;
    }
	
	
	/* 
	���������tmp=123;
	  ��һ��ѭ����
		buf[0] = 3 + '0', temp = 12;
	  �ڶ���ѭ����
		buf[1] = 2 + '0', temp = 1;
	  ������ѭ����
		buf[2] = 1 + '0', temp = 0; 
	���������������buf�У�����+ '0'��str_to_intһ����Ҳ��������ASCII��
	buf�е��ڴ水char��������תΪ�� �ַ��͵�����
	*/
   
    len = (n < 0 ? ++i: i);  //���n�Ǹ����������Ҫһλ���洢����
	
    str[i] = 0;            //ĩβ�ǽ�����0���Ҿ����� '\0'
	
	//��buf��������ַ������ַ���������Ǹ�����str[i]
    while(i--)
    {
		if (buf[len-i-1] == 0)
        {			
            break;
        }
        str[i] = buf[len-i-1];  
    }
	
	//����Ǹ��������һ�����ţ�
    if (i == 0 )
    {
        str[i] = '-';          
    }
}


// �������ܣ���ʮ����numת��bcd��Ʃ���56ת��0x56
unsigned int num_2_bcd(unsigned int num)
{
	// ��һ������56��ֳ�5��6 
	// �ڶ�������5��6��ϳ�0x56
	return (((num / 10)<<4) | (num % 10));
}
/*
@��������Ϊ��int�ĳ������ó����������������(num / 10���Ľ����ʮλ�����Ǹ����֣�����
4λҲ����ʮ�����Ƶ�2λ��%��ȡ�������ţ��õ����Ǹ�λ������Ҳ��������λ�ˣ��õ���ʮ��������
���ظ���void rtc_set_time(const struct rtc_time *p)���
*/


// �������ܣ���bcd��numת��ʮ���ƣ�Ʃ���0x56ת��56
unsigned int bcd_2_num(unsigned int bcd)
{
	// ��һ������0x56��ֳ�5��6 
	// �ڶ�������5��6��ϳ�56
	return (((bcd & 0xf0)>>4)*10 + (bcd & (0x0f)));
}


/*FROM �ٿ� ����s1���Ƿ����s2��������������ҵ��ĵ�һ����ĸ��ָ��*/ 
// ������s1="linux hello" s2="nu" ��ô���������� �ַ� "nux hello" 
char *mystrstr(char *s1, char *s2)  
{  
    int n; 
	
    if (*s2)                      //�����������  
    {  
        while (*s1)                 
        {  
            for (n=0; *(s1+n)==*(s2+n); n++)  
            {  
                if (!*(s2+n+1))            //���ҵ���һ���ַ��Ƿ�Ϊ'\0'  
                {  
                    return s1;  
                }  
            }  
            s1++;  
        }  
        return NULL;  
    }  
    else  
    {  
        return s1;  
    }  
}


// �������ܣ��ȶ��������ո���ַ������׵����Ƿ���ͬ��
// �������ԣ������ַ����Ƿ��пո񶼻���������������û�в������Ļ��ƣ�
int strcmp_first_word(const char *store, const char *input)
{
	// ֱ�ӱȶ�֪�����ֵ�һ���ո�,
	while ((*store != ' ') || (*input != ' '))
	{				
		if (*store++ != *input++)	
			return -1;	
	}		
	return 1;	
}

#if 0

// ���ַ���str���տո�ָ��ɶ���ַ��������η����ַ���������
// ע�⴫�ε��ַ���ά��������ʵ��� ���򱨴�error: array type has incomplete element type������char cmd[][100]
void str_split_array(char cmd[][], const char *str)
{
	int m = 0, n = 0;	// m��ʾ��λ�����һά��n��ʾ�ڶ�ά
	
	while (*str != '\0')
	{
		if (*str != ' ')
		{
			cmd[m][n] = *str;
			n++;
		}
		else
		{
			cmd[m][n] = '\0';
			n = 0;
			m++;
		}
		str++;
	}
	cmd[m][n] = '\0';
	
	//printf("cmd[0] = %s, cmd[1] = %s, cmd[2] = %s.\n", cmd[0], cmd[1], cmd[2]);
}
#endif


/**
 * ���Զ���ȶԳ����£��������ַ����Ƿ���ȫ��ͬ����ͬ����0����ͬ���ط�0
 * ���磺 cs = "lishichang" ct = "lishis" 
 * ���� count = 5�� ����ȫ��ͬ������ֵ = 0
 * ���� count = 6�� ���� 'c' - 's'���²�ͬ������ֵ ��0
 *
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int mystrncmp(const char * cs,const char * ct,size_t count)
{
	register signed char __res = 0;

	while (count) 
	{
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
				
		count--;
	}

	return __res;
}


/**
 * strchr - Find the first occurrence of a character in a string
 * @s: The string to be searched
 * @c: The character to search for
 */
// ����s�а����ַ�c����ô���ص�һ�γ���c֮����ַ��������򷵻�NULL
char * mystrchr(const char * s, int c)
{
	for(; *s != (char) c; ++s)
		if (*s == '\0')
			return NULL;
		
	return (char *) s;
}

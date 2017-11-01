#include "stdio.h"
#include "public.h"

/*
 *	描述：本文件是 收集的裸机下的功能函数，比如字符串的处理函数	
 *
 *
 */




// 字符串数字转换为纯整形数字
unsigned int str_to_int(const char* str)
{
    int i=0, num=0;   
  
    for(i=0; str[i]!='\0'; i++)
	{  	
		//保证是数字字符串
        if( (str[i] >= '0') && (str[i] <= '9') )	
			// 利用ASCII码的错位实现
			num = num*10 + (str[i]-'0');
		else
		{
			printf(" parame error! .\n ");
			return 0;
		}
    }  
     
    return num;  
}

// 这个函数暂时有bug 输入数字0 无法输出字符串的"0",当然这个bug已经顺利解决了
void int_to_str(int n, char *str)
{
    char buf[10] = "";
    int i = 0;
    int len = 0;
    int temp = n < 0 ? -n: n;  // temp为n的绝对值
  
	// 参数错误检查，str必须有内存空间
    if (str == NULL)
    {
        return;
    }
	// 以0开头整数的处理办法，假如int 098，其实这是这是一个不合法的有符号整数
	// 所以我认为有必要加上对 0 的处理方法
	if (n == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return;
	}
	
	 //把temp的每一位上的数存入buf
    while(temp)
    {
        buf[i++] = (temp % 10) + '0'; 
        temp = temp / 10;
    }
	
	
	/* 
	解析：如果tmp=123;
	  第一轮循环：
		buf[0] = 3 + '0', temp = 12;
	  第二轮循环：
		buf[1] = 2 + '0', temp = 1;
	  第三轮循环：
		buf[2] = 1 + '0', temp = 0; 
	这样就逆序放在了buf中，至于+ '0'和str_to_int一样，也是利用了ASCII码
	buf中的内存按char来解析即转为了 字符型的数字
	*/
   
    len = (n < 0 ? ++i: i);  //如果n是负数，则多需要一位来存储负号
	
    str[i] = 0;            //末尾是结束符0，我觉的是 '\0'
	
	//把buf数组里的字符拷到字符串，如果是负数，str[i]
    while(i--)
    {
		if (buf[len-i-1] == 0)
        {			
            break;
        }
        str[i] = buf[len-i-1];  
    }
	
	//如果是负数，添加一个负号，
    if (i == 0 )
    {
        str[i] = '-';          
    }
}


// 函数功能：把十进制num转成bcd，譬如把56转成0x56
unsigned int num_2_bcd(unsigned int num)
{
	// 第一步，把56拆分成5和6 
	// 第二步，把5和6组合成0x56
	return (((num / 10)<<4) | (num % 10));
}
/*
@解析：因为是int的除法，得出结果是整数，所以(num / 10）的结果是十位数的那个数字，左移
4位也就是十六进制的2位；%是取余数符号，得到的是各位数而且也不用再移位了！得到的十六进制数
返回给了void rtc_set_time(const struct rtc_time *p)那里！
*/


// 函数功能：把bcd码num转成十进制，譬如把0x56转成56
unsigned int bcd_2_num(unsigned int bcd)
{
	// 第一步，把0x56拆分成5和6 
	// 第二步，把5和6组合成56
	return (((bcd & 0xf0)>>4)*10 + (bcd & (0x0f)));
}


/*FROM 百科 产看s1中是否包含s2，如果包含返回找到的第一个字母的指针*/ 
// 举例：s1="linux hello" s2="nu" 那么本函数返回 字符 "nux hello" 
char *mystrstr(char *s1, char *s2)  
{  
    int n; 
	
    if (*s2)                      //两种情况考虑  
    {  
        while (*s1)                 
        {  
            for (n=0; *(s1+n)==*(s2+n); n++)  
            {  
                if (!*(s2+n+1))            //查找的下一个字符是否为'\0'  
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


// 函数功能：比对两个带空格的字符串的首单词是否相同！
// 经过测试，无论字符串是否有空格都会正常工作，但是没有参数检查的机制！
int strcmp_first_word(const char *store, const char *input)
{
	// 直接比对知道出现第一个空格,
	while ((*store != ' ') || (*input != ' '))
	{				
		if (*store++ != *input++)	
			return -1;	
	}		
	return 1;	
}

#if 0

// 将字符串str按照空格分隔成多个字符串，依次放入字符串数组中
// 注意传参的字符二维数组是有实体的 否则报错：error: array type has incomplete element type，比如char cmd[][100]
void str_split_array(char cmd[][], const char *str)
{
	int m = 0, n = 0;	// m表示二位数组第一维，n表示第二维
	
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
 * 在自定义比对长度下，看两个字符串是否完全相同，相同返回0，不同返回非0
 * 例如： cs = "lishichang" ct = "lishis" 
 * 假如 count = 5， 则完全相同，返回值 = 0
 * 假如 count = 6， 则导致 'c' - 's'导致不同，返回值 非0
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
// 假如s中包含字符c，那么返回第一次出现c之后的字符串，否则返回NULL
char * mystrchr(const char * s, int c)
{
	for(; *s != (char) c; ++s)
		if (*s == '\0')
			return NULL;
		
	return (char *) s;
}

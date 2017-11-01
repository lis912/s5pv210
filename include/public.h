#ifndef __PUBLIC_H
#define __PUBLIC_H


// 字符串数字转换为纯整形数字
unsigned int str_to_int(const char* str);

// 函数功能：把十进制num转成bcd，譬如把56转成0x56
unsigned int num_2_bcd(unsigned int num);

// 函数功能：把bcd码num转成十进制，譬如把0x56转成56
unsigned int bcd_2_num(unsigned int bcd);

//查看s1中是否包含s2，如果包含返回找到的第一个字母的指针
// 举例：s1="linux hello" s2="nu" 那么本函数返回 字符 "nux hello" 
char *mystrstr(char *s1, char *s2);

// 假如s中包含字符c，那么返回第一次出现c之后的字符串，否则返回NULL
char * mystrchr(const char * s, int c);

// 函数功能：比对两个带空格的字符串的首单词是否相同！
int strcmp_first_word(const char *store, const char *input);

// 在自定义比对长度下，看两个字符串是否完全相同，相同返回0，不同返回非0
int mystrncmp(const char * cs,const char * ct,size_t count);

#endif
#ifndef __PUBLIC_H
#define __PUBLIC_H


// �ַ�������ת��Ϊ����������
unsigned int str_to_int(const char* str);

// �������ܣ���ʮ����numת��bcd��Ʃ���56ת��0x56
unsigned int num_2_bcd(unsigned int num);

// �������ܣ���bcd��numת��ʮ���ƣ�Ʃ���0x56ת��56
unsigned int bcd_2_num(unsigned int bcd);

//�鿴s1���Ƿ����s2��������������ҵ��ĵ�һ����ĸ��ָ��
// ������s1="linux hello" s2="nu" ��ô���������� �ַ� "nux hello" 
char *mystrstr(char *s1, char *s2);

// ����s�а����ַ�c����ô���ص�һ�γ���c֮����ַ��������򷵻�NULL
char * mystrchr(const char * s, int c);

// �������ܣ��ȶ��������ո���ַ������׵����Ƿ���ͬ��
int strcmp_first_word(const char *store, const char *input);

// ���Զ���ȶԳ����£��������ַ����Ƿ���ȫ��ͬ����ͬ����0����ͬ���ط�0
int mystrncmp(const char * cs,const char * ct,size_t count);

#endif
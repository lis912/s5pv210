#ifndef __RTC_H
#define __RTC_H__

#define 	RTC_BASE	 (0xE2800000)
#define		rINTP      	 (*((volatile unsigned long *)(RTC_BASE + 0x30)))
#define		rRTCCON    	 (*((volatile unsigned long *)(RTC_BASE + 0x40)))
#define		rTICCNT    	 (*((volatile unsigned long *)(RTC_BASE + 0x44)))
#define		rRTCALM    	 (*((volatile unsigned long *)(RTC_BASE + 0x50)))
#define		rALMSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x54)))
#define		rALMMIN    	 (*((volatile unsigned long *)(RTC_BASE + 0x58)))
#define		rALMHOUR  	 (*((volatile unsigned long *)(RTC_BASE + 0x5c)))
#define		rALMDATE     (*((volatile unsigned long *)(RTC_BASE + 0x60)))
#define		rALMMON    	 (*((volatile unsigned long *)(RTC_BASE + 0x64)))
#define		rALMYEAR  	 (*((volatile unsigned long *)(RTC_BASE + 0x68)))
#define		rRTCRST      (*((volatile unsigned long *)(RTC_BASE + 0x6c)))
#define		rBCDSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x70)))
#define		rBCDMIN   	 (*((volatile unsigned long *)(RTC_BASE + 0x74)))
#define		rBCDHOUR     (*((volatile unsigned long *)(RTC_BASE + 0x78)))
#define		rBCDDATE     (*((volatile unsigned long *)(RTC_BASE + 0x7c)))
#define		rBCDDAY      (*((volatile unsigned long *)(RTC_BASE + 0x80)))
#define		rBCDMON      (*((volatile unsigned long *)(RTC_BASE + 0x84)))
#define		rBCDYEAR     (*((volatile unsigned long *)(RTC_BASE + 0x88)))
#define		rCURTICCNT   (*((volatile unsigned long *)(RTC_BASE + 0x90)))
#define		rRTCLVD    	 (*((volatile unsigned long *)(RTC_BASE + 0x94)))

struct rtc_time
{
	unsigned int year;
	unsigned int month;
	unsigned int date;			// ¼¸ºÅ
	unsigned int hour;			
	unsigned int minute;
	unsigned int second;
	unsigned int day;			// ÐÇÆÚ¼¸
};

void rtc_set_time(const struct rtc_time *p);
void rtc_get_time(struct rtc_time *p);
void isr_rtc_alarm(void);
void rtc_set_alarm(void);


#endif
#ifndef __ADC_H
#define __ADC_H

#define TSADCCON0		0xE1700000
#define TSDATX0			0xE170000C
#define TSDATY0			0xE1700010
//#define CLRINTADC0		0xE1700000
#define ADCMUX			0xE170001C

#define rTSADCCON0		(*(volatile unsigned int *)TSADCCON0)
#define rTSDATX0		(*(volatile unsigned int *)TSDATX0)
#define rTSDATY0		(*(volatile unsigned int *)TSDATY0)
//#define rCLRINTADC0		(*(volatile unsigned int *)CLRINTADC0)
#define rADCMUX			(*(volatile unsigned int *)ADCMUX)


// ����ADC����ɵĹ��ܾ���ѭ�����ADC���õ�ADCת������ֵ��ӡ����
void adc_test(void);










#endif
#include "main.h"

#define CONVERSION_12BIT				(1<<16)
#define PRESCALER_EN					(1<<14)
#define PRESCALER_VAL_65				(65<<6)
#define NORMAL_MODE						~(1<<2)
#define DIS_START_BY_READ_MODE			~(1<<1)
#define ADC_CHANNEL0					~(0x0F<<0)
#define START_CONVERSION				(1<<0)


// ��ʼ��ADC�������ĺ���
static void adc_init(void)
{
	rTSADCCON0	|= CONVERSION_12BIT;		// resolution set to 12bit
	rTSADCCON0	|= PRESCALER_EN;			// enable clock prescaler
	rTSADCCON0 	&= ~(0xFF<<6);
	rTSADCCON0	|= PRESCALER_VAL_65;	// convertor clock = 66/66M=1MHz, MSPS=200KHz
	rTSADCCON0 	&= NORMAL_MODE;						// normal operation mode
	rTSADCCON0 	&= DIS_START_BY_READ_MODE;			// disable start by read mode
	
	rADCMUX		&= ADC_CHANNEL0;			// MUXѡ��ADCIN0,ѡ��ͨ��0
}




// ����ADC����ɵĹ��ܾ���ѭ�����ADC���õ�ADCת������ֵ��ӡ����
void adc_test(void)
{
	unsigned int val = 0;
	
	adc_init();
	
	while (1)
	{
		// ��һ�����ֹ�����ADCת��
		rTSADCCON0	|= START_CONVERSION;
		// �ڶ������ȴ�ADCת�����
		while (!(rTSADCCON0 & (1<<15)));  // End of conversion flag(Read only) =1(end)
		
		// ����������ȡADC������ֵ
		// ���Ĳ�������/��ʾ����ֵ
		val = rTSDATX0;
		// bit14ʵ�ʲ��Զ���Ϊ0 = Normal ADC conversion
		printf("x: bit14 = %d.\n", (val & (1<<14)));
		// X-Position conversion data value (includes normal ADC conversion data value)
		printf("x: adc value = %d.\n", (val & (0xFFF<<0)));
		
		val = rTSDATY0;
		// �����Y���Ǵ�����ʹ�õ��ģ�����û��ʹ��Y���ģ�������
		// ����ʵ��������� ���� 0
		printf("y: bit14 = %d.\n", (val & (1<<14)));
		printf("y: adc value = %d.\n", (val & (0xFFF<<0)));

		// ���岽����ʱ2��
		delays(2);
	}
	
}























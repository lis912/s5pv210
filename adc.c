#include "main.h"

#define CONVERSION_12BIT				(1<<16)
#define PRESCALER_EN					(1<<14)
#define PRESCALER_VAL_65				(65<<6)
#define NORMAL_MODE						~(1<<2)
#define DIS_START_BY_READ_MODE			~(1<<1)
#define ADC_CHANNEL0					~(0x0F<<0)
#define START_CONVERSION				(1<<0)


// 初始化ADC控制器的函数
static void adc_init(void)
{
	rTSADCCON0	|= CONVERSION_12BIT;		// resolution set to 12bit
	rTSADCCON0	|= PRESCALER_EN;			// enable clock prescaler
	rTSADCCON0 	&= ~(0xFF<<6);
	rTSADCCON0	|= PRESCALER_VAL_65;	// convertor clock = 66/66M=1MHz, MSPS=200KHz
	rTSADCCON0 	&= NORMAL_MODE;						// normal operation mode
	rTSADCCON0 	&= DIS_START_BY_READ_MODE;			// disable start by read mode
	
	rADCMUX		&= ADC_CHANNEL0;			// MUX选择ADCIN0,选择通道0
}




// 测试ADC，完成的功能就是循环检测ADC并得到ADC转换数字值打印出来
void adc_test(void)
{
	unsigned int val = 0;
	
	adc_init();
	
	while (1)
	{
		// 第一步：手工开启ADC转换
		rTSADCCON0	|= START_CONVERSION;
		// 第二步：等待ADC转换完毕
		while (!(rTSADCCON0 & (1<<15)));  // End of conversion flag(Read only) =1(end)
		
		// 第三步：读取ADC的数字值
		// 第四步：处理/显示数字值
		val = rTSDATX0;
		// bit14实际测试读出为0 = Normal ADC conversion
		printf("x: bit14 = %d.\n", (val & (1<<14)));
		// X-Position conversion data value (includes normal ADC conversion data value)
		printf("x: adc value = %d.\n", (val & (0xFFF<<0)));
		
		val = rTSDATY0;
		// 这里的Y轴是触摸屏使用到的，这里没有使用Y轴的模拟量输出
		// 所以实际输出这里 都是 0
		printf("y: bit14 = %d.\n", (val & (1<<14)));
		printf("y: adc value = %d.\n", (val & (0xFFF<<0)));

		// 第五步：延时2秒
		delays(2);
	}
	
}























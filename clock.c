#include "main.h"

void clock_init(void)
{
	// 1 ���ø���ʱ�ӿ��أ���ʱ��ʹ��PLL
	rREG_CLK_SRC0 = 0x0;
	
	// 2 ��������ʱ�䣬ʹ��Ĭ��ֵ����
	// ����PLL��ʱ�Ӵ�Fin������Ŀ��Ƶ��ʱ����Ҫһ����ʱ�䣬������ʱ��
	rREG_APLL_LOCK = 0x0000ffff;
	rREG_MPLL_LOCK = 0x0000ffff;
	
	// 3 ���÷�Ƶ
	// ��bit[0~31]
	rREG_CLK_DIV0 = 0x14131440;
	
	// 4 ����PLL
	// FOUT = MDIV*FIN/(PDIV*2^(SDIV-1))=0x7d*24/(0x3*2^(1-1))=1000 MHz
	rREG_APLL_CON0 = APLL_VAL;
	// FOUT = MDIV*FIN/(PDIV*2^SDIV)=0x29b*24/(0xc*2^1)= 667 MHz
	rREG_MPLL_CON = MPLL_VAL;
	
	// 5 ���ø���ʱ�ӿ���,ʹ��PLL
	rREG_CLK_SRC0 = 0x10001111;
}














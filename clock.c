#include "main.h"

void clock_init(void)
{
	// 1 设置各种时钟开关，暂时不使用PLL
	rREG_CLK_SRC0 = 0x0;
	
	// 2 设置锁定时间，使用默认值即可
	// 设置PLL后，时钟从Fin提升到目标频率时，需要一定的时间，即锁定时间
	rREG_APLL_LOCK = 0x0000ffff;
	rREG_MPLL_LOCK = 0x0000ffff;
	
	// 3 设置分频
	// 清bit[0~31]
	rREG_CLK_DIV0 = 0x14131440;
	
	// 4 设置PLL
	// FOUT = MDIV*FIN/(PDIV*2^(SDIV-1))=0x7d*24/(0x3*2^(1-1))=1000 MHz
	rREG_APLL_CON0 = APLL_VAL;
	// FOUT = MDIV*FIN/(PDIV*2^SDIV)=0x29b*24/(0xc*2^1)= 667 MHz
	rREG_MPLL_CON = MPLL_VAL;
	
	// 5 设置各种时钟开关,使用PLL
	rREG_CLK_SRC0 = 0x10001111;
}














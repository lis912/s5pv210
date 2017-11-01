	
	本文件夹是在裸机下移植linux系统stdio标准库的printf函数，需要注意以下几点：
1. 此printf函数截取自linux内核，但是底层调用的putc函数是需要裸机下提供的！
2. 本文件的标准输出是串口，具体输出的串口配置选择UART0还是UART2在uart.h中配置
3. printf核心：串口初始化， putc函数编写， 标准库移植， makefile配置


												2017年8月20日
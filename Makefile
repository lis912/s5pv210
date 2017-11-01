CC		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump
AR		= arm-linux-ar

INCDIR	:= $(shell pwd)
# C预处理器的flag，flag就是编译器可选的选项
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include
# C编译器的flag -fno-builtin 屏蔽内建函数
CFLAGS		:= -Wall -O2 -fno-builtin

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o clock.o uart.o sdram_init.o sd_relocate.o main.o
objs += interrupt.o
objs += led.o
objs += pwm.o
objs += interupt_key.o
objs += delay.o
objs += wdt.o
objs += rtc.o
objs += pubfunc/public.o
objs += lib/libc.a
objs += adc.o
objs += shell.o
objs += bootdelay.o
objs += g_cmd.o
objs += env.o


usb.bin: $(objs)
	$(LD) -Tlink.lds -o 210_usb.elf $^
	$(OBJCOPY) -O binary 210_usb.elf usb.bin
	$(OBJDUMP) -D 210_usb.elf > 210_usb_elf.dis
	gcc mkv210_sd_image.c -o mkv210_sd_image
	./mkv210_sd_image usb.bin 210_sd.bin

lib/libc.a:
	cd lib;	make;	cd .. 
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

pubfunc/public.o :
	cd pubfunc; make; cd ..

clean:
	rm *.o *.elf *.bin *.dis mkv210_sd_image -f
	cd lib; make clean; cd ..
	cd pubfunc; make clean; cd ..

	
	
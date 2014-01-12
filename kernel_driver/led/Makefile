## 2440x kernel path
CC = /usr/local/DMA-2440XP/bin/arm-linux-gcc
2440X_KERNEL_DIR = ../kernel

ifneq ($(KERNELRELEASE),)
	obj-m := led.o
else
	KERNELDIR ?= $(2440X_KERNEL_DIR)
	
	PWD := $(shell pwd)
	
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	
clean:
	rm -f *.ko *.o
endif 



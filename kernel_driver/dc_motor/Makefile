## s3c2440 kernel path
CC =/usr/local/DMA-2440XP/bin/arm-linux-gcc
S3C2440_KERNEL_DIR = ../kernel
ifneq ($(KERNELRELEASE),)
	obj-m := dc_motor.o
else
	KERNELDIR ?= $(S3C2440_KERNEL_DIR)
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
##	rm -rf *.o *.mod.* *.ko *.o.* .*.*.cmd .tmp_versions
	rm -f *.ko *.o
endif 

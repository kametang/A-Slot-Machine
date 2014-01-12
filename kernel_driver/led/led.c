// ------------------------------------------------------------------------------------------
// File:            kernel_driver/led/led.c
// Description:     LED Driver for DMA-2440XP
// Version:         0.1.0
// Author:          Ching-Tang, Chang <km-work@tth.twbbs.org>
// Source:          dmatek <www.dmatek.com>
// 
// Copyright (C) 2013 A Slot Machine
// ------------------------------------------------------------------------------------------

#include <linux/config.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
#include <asm/delay.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch/regs-mem.h>

#define LED_MAJOR   203
#define led_name    "led"

#define LED_ON      0
#define LED_OFF     1
#define LED_8X8     2

static int __iomem * LED8X8_Address;

typedef struct _LED_PARAM{
    unsigned int num;
}LED_PARAM;

typedef struct _KEY_PARAM{
    unsigned int state;
}KEY_PARAM;

typedef struct _LED_MAP{
    u16 map[8];
    u32 d;
}LED_MAP;


#define MS_DELAY(s) Delay(s<<3)
#define S3C2440A_FCLK 400000000
void Delay(int time)
{
    volatile int i, j = 0;
    volatile static int loop = S3C2440A_FCLK/100000;

    while(time--)
        for(i = 0; i < loop; i++) { j++; }
}

void LED8X8_Display(u16 *LED8X8, u32 d)
{
    u16 m;
    while(d--){
        for(m = 0; m < 8; m++){
            *LED8X8_Address = ((1<<(8+m))&0xff00) | ((~(LED8X8[m]))&0x00ff);
            MS_DELAY(2);
        }
    }
}

#define LED_OFFSET  4
static void led_on(int num)
{
    int gpfdat;
    gpfdat = __raw_readl(S3C2410_GPFDAT);
    if(num < 4 && num >= 0)
        gpfdat &= ~(1<<(num+LED_OFFSET));
    __raw_writel(gpfdat, S3C2410_GPFDAT);
}

static void led_off(int num)
{
    int gpfdat;
    gpfdat = __raw_readl(S3C2410_GPFDAT);
    if(num < 4 && num >= 0)
        gpfdat |= (1<<(num+LED_OFFSET));
    __raw_writel(gpfdat, S3C2410_GPFDAT);
}

static ssize_t led_read(struct file *filp,char *buf,size_t count,loff_t *l)
{
    return count;
}

static ssize_t led_write(struct file *filp,const char *buf,size_t count,loff_t *f_ops)
{
    return count;
}

static int led_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    int num;
    LED_MAP map;

    if(cmd == LED_8X8){
        ret = copy_from_user(&map, (unsigned long*)arg, sizeof(map));
        if(ret != 0){
            printk("gpio_ioctl: copy_from_user failed\n");
            return(-EFAULT);
        }
        LED8X8_Display(map.map, map.d);
    }
    else{
        ret = copy_from_user(&num, (int*)arg, sizeof(int));
        if(ret != 0){
            printk("gpio_ioctl: copy_from_user failed\n");
            return(-EFAULT);
        }
        if(cmd == LED_ON)
            led_on(num);
        else if(cmd == LED_OFF)
            led_off(num);
    }
    return 0;
}

static int led_open(struct inode *inode, struct file *filp)
{
    s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF4_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF5, S3C2410_GPF5_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF6, S3C2410_GPF6_OUTP);
    s3c2410_gpio_cfgpin(S3C2410_GPF7, S3C2410_GPF7_OUTP);

    return 0;
}   

static int led_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static struct file_operations led_fops = 
{
    owner   :    THIS_MODULE,
    read    :   led_read,
    write   :   led_write,
    ioctl   :   led_ioctl,
    open    :   led_open,
    release :   led_release,
};

static int __init led_init(void)
{
    int retval;
    int bwscon;
    int bankcon1;
    
    retval = register_chrdev(LED_MAJOR,led_name,&led_fops);
    if(retval < 0)
    {
        printk(KERN_WARNING"Can't get major %d\n",LED_MAJOR);
        return retval;
    }
    s3c2410_gpio_cfgpin(S3C2410_GPA12, S3C2410_GPA12_nGCS1);
    bwscon = __raw_readl(S3C2410_BWSCON);
    bwscon&= ~(0xF << 4);
    bwscon|= (0x6 << 4);
    __raw_writel(bwscon, S3C2410_BWSCON);
    
    bankcon1 = __raw_readl(S3C2410_BANKCON1);
    bankcon1 =((0x3<<13)+(0x3<<11)+(0x7<<8)+(0x3<<6)\
        +(0x3<<4)+(0x3<<2)+(0x0));
    __raw_writel(bankcon1, S3C2410_BANKCON1);
    
    LED8X8_Address = ioremap(0x08000000,4);
    if (LED8X8_Address == 0) {
        printk(KERN_INFO  "failed to ioremap() region\n");
        return -EINVAL;
    }
    // printk("LED driver register success!\n");
    return 0;
}

static void __exit led_exit(void)
{
    unregister_chrdev(LED_MAJOR,led_name);
    printk("LED driver release success!\n");

}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DMATEK Co., Ltd <http://www.dmatek.com.tw>");
MODULE_DESCRIPTION("led  driver");

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

#include <asm/io.h>
#include <asm/hardware/clock.h>
#include <asm/arch/regs-gpio.h>
#include <asm/arch/regs-timer.h>


#include "dc_motor.h"



#define DCM_MAJOR 201
#define DCM_MINOR 0
#define dcm_name "DCM"


#define MAX_VAL 90
#define FREQ_PWM1 1000

static void set_pwm3(unsigned char hiratio)
{
    unsigned long tcnt;
    printk("hiratio = %d",hiratio);
    tcnt =( 96000000 )/( FREQ_PWM1 *16 );
    __raw_writel(((tcnt*(hiratio))/100), S3C2410_TCMPB(3));
}

static ssize_t dcm_read(struct file *filp,char *buf,size_t count,loff_t *l)
{
    return count;
}

static ssize_t dcm_write(struct file *filp,const char *buf,size_t count,loff_t *f_ops)
{
    return count;
}

static int dcm_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd){
        case SPEED_NORMAL:
            set_pwm3(SPEED_NORMAL);
            break;
        case SPEED_HIGH:
            set_pwm3(SPEED_HIGH);
            break;
        case SPEED_OFF:
            set_pwm3(SPEED_OFF);
            break;
        default:
            break;
    }
    return 0;
}

static int dcm_open(struct inode *inode, struct file *filp)
{

    return 0;
}

static int dcm_release(struct inode *inode, struct file *filp)
{
    set_pwm3(0);
    return 0;
}

static struct file_operations dcm_fops = 
{
    owner:   THIS_MODULE,
    read    :   dcm_read,
    write   :   dcm_write,
    ioctl   :   dcm_ioctl,
    open    :   dcm_open,
    release :   dcm_release,
};

static void gpio_init(void)
{
    unsigned long tcon;
    unsigned long tcnt;
    unsigned long tcfg1=0;
    unsigned long tcfg0=0;
        s3c2410_gpio_cfgpin(S3C2410_GPB3, S3C2410_GPB3_TOUT3);
    tcon = __raw_readl(S3C2410_TCON);
    tcon &= ~(0xf0000); // stop timer 3

    __raw_writel(tcon, S3C2410_TCON);

    tcfg1 &= ~S3C2410_TCFG1_MUX3_MASK;
    tcfg1 |= S3C2410_TCFG1_MUX3_DIV2; //25M

    tcfg0 &= ~S3C2410_TCFG_PRESCALER1_MASK;
    tcfg0 |= (32<<8); // 50m/2/(32+1)
    __raw_writel(tcfg1, S3C2410_TCFG1);
    __raw_writel(tcfg0, S3C2410_TCFG0);

    tcnt =( 96000000 )/( FREQ_PWM1 *16 );
    __raw_writel(tcnt, S3C2410_TCNTB(3));
    __raw_writel(((tcnt*(50))/100), S3C2410_TCMPB(3));

    tcon = __raw_readl(S3C2410_TCON);
    tcon &= ~(0xf0000);
    tcon |= (S3C2410_TCON_T3MANUALUPD|S3C2410_TCON_T3RELOAD);
    __raw_writel(tcon, S3C2410_TCON);
    tcon &= ~(0xf0000);
    tcon |= (S3C2410_TCON_T3START  |S3C2410_TCON_T3RELOAD);
    __raw_writel(tcon, S3C2410_TCON);
    
    set_pwm3(0);
}

static int __init dcm_init(void)
{
    int retval;
    retval = register_chrdev(DCM_MAJOR,dcm_name,&dcm_fops);
    if(retval < 0)
    {
        printk(KERN_WARNING"Can't get major %d\n",DCM_MAJOR);
        return retval;
    }
    gpio_init();
    printk("step driver register success!\n");
    return 0;
}
static void __exit dcm_exit(void)
{
    unregister_chrdev(DCM_MAJOR,dcm_name);
    printk("step driver release success!\n");

}
module_init(dcm_init);
module_exit(dcm_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("DMATEK Co., Ltd <http://www.dmatek.com.tw>");
MODULE_DESCRIPTION("dc motor driver");
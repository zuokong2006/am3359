
#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
//#include <asm/irq.h>


/* 设备名 */
#define DEVICE_NAME		"leds"

/* led */
static unsigned long bb_led_tab[] = {53, 54, 55, 56};

/* ioctl function */
static int bb_led_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 
{
	int ret = 0;
	
	printk("ioctl fn: arg=%d, cmd=%d\r\n", arg, cmd);
	if(4 < arg)
	{
		return -1;
	}
	
	switch(cmd)
	{
		case 0:
			gpio_set_value(bb_led_tab[arg], 0);
			ret = 0;
			break;
		case 1:
			gpio_set_value(bb_led_tab[arg], 1);
			ret = 0;
			break;
		default:
			ret = -1;
			break;
	}
	
	return ret;
}

/* 文件操作结构体 */
static struct file_operations dev_fops = 
{
	.owner = THIS_MODULE,
	.unlocked_ioctl = bb_led_ioctl, 
};
static struct miscdevice misc = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

/* 模块加载函数 */
static int __init bb_led_init(void)
{
	int ret = 0, i = 0;
	
	/* 设置GPIO */
	for(i=0; i<4; i++)
	{
		/* 设置端口为输出状态，内核已初始化 */
		gpio_set_value(bb_led_tab[i], 1);
	}
	/*注册混杂型字符设备驱动*/
    ret = misc_register(&misc);
	printk("led driver module init!\n");
	
	return ret;
}

/* 模块卸载函数 */
static void __exit bb_led_exit(void)
{
	int i = 0;
	
	for(i=0; i<4; i++)
	{
		/* 设置端口为输出状态，内核已初始化 */
		gpio_set_value(bb_led_tab[i], 0);
	}
	/*注销混杂型字符设备驱动*/
    misc_deregister(&misc);
	printk("led driver module exit!\n");
}

module_init(bb_led_init);
module_exit(bb_led_exit);

MODULE_AUTHOR("zuokong");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("BB led driver");




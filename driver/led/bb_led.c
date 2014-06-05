
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#define TIMEOUT			2 /* 2�� */
#define TIMER_EXPIRES	(jiffies+TIMEOUT*HZ)
/* �豸�� */
#define DEVICE_NAME		"leds"

/* led */
static const unsigned long bb_led_tab[] = {53, 54, 55, 56};
static struct timer_list s_stTimer = {0};
static int lastio = 0;

dev_t led_dev;
struct cdev *led_cdev;


/* ��ʱ����ִ�еĺ��� */
static void timer_cb(unsigned long ulArg)
{
	int io = 0;

	//printk("Time up!\n");
	mod_timer(&s_stTimer, TIMER_EXPIRES);
	io = gpio_get_value(bb_led_tab[3]);
	//printk("io=%d\r\n", io);
	if(0 != lastio)
	{
		lastio = 0;
	}
	else
	{
		lastio = 1;
	}
	gpio_set_value(bb_led_tab[3], lastio);
}

/* open */
static int bb_led_open(struct inode *inode, struct file *filp)
{
	printk("led device is open!\r\n");
	return 0;
}

/* release */
static int bb_led_release(struct inode *inode, struct file *filp)
{
	printk("led device is release!\r\n");
	return 0;
}

/* ioctl */
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

/* �ļ������ṹ�� */
static struct file_operations dev_fops = 
{
	.owner = THIS_MODULE,
	.open = bb_led_open,
	.release = bb_led_release,
	.unlocked_ioctl = bb_led_ioctl, 
};

/* ģ����غ��� */
static int __init bb_led_init(void)
{
	int ret = 0;

	/* */
	ret = alloc_chrdev_region(&led_dev, 0, 1, DEVICE_NAME);
	if(0 > ret)
	{
		printk("alloc_chrdev_region return < 0\r\n");
		return -1;
	}
	led_cdev = cdev_alloc();
	if(NULL == led_cdev)
	{
		printk("register led_cdev error!\r\n");
		return -1;
	}
	cdev_init(led_cdev, &dev_fops);
	led_cdev->ops = &dev_fops;
	led_cdev->owner = THIS_MODULE;
	if(cdev_add(led_cdev, led_dev, 1))
	{
		printk("someting wrong when adding led_cdev!\r\n");
		return -1;
	}
	else
	{
		printk("success adding led_cdev!\r\n");
	}
	
	gpio_set_value(bb_led_tab[3], 1);
	gpio_set_value(bb_led_tab[2], 1);
	/* ��ʼ����ʱ�� */
	init_timer(&s_stTimer);
	s_stTimer.expires = TIMER_EXPIRES;
	s_stTimer.function = timer_cb;
	s_stTimer.data = 0;
	add_timer(&s_stTimer);
	printk("led driver init!\n");
	
	return 0;
}

/* ģ��ж�غ��� */
static void __exit bb_led_exit(void)
{
	gpio_set_value(bb_led_tab[3], 0);
	gpio_set_value(bb_led_tab[2], 0);
	del_timer(&s_stTimer);
	
	cdev_del(led_cdev);
	unregister_chrdev_region(led_dev, 1);
	
	printk("led driver exit!\n");
}

module_init(bb_led_init);
module_exit(bb_led_exit);

MODULE_AUTHOR("zuokong");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Timer test module");




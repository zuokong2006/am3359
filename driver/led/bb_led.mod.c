#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa60b9ee, "module_layout" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x532bdb3a, "cdev_del" },
	{ 0xc996d097, "del_timer" },
	{ 0xbe2c0274, "add_timer" },
	{ 0x593a99b, "init_timer_key" },
	{ 0x3afdbb64, "cdev_add" },
	{ 0x12bee511, "cdev_init" },
	{ 0xbc1e2c81, "cdev_alloc" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x7d11c268, "jiffies" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0x8834396c, "mod_timer" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6A329C3AC6C6F97B51D93D7");

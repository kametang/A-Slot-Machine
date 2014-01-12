#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

#undef unix
struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = __stringify(KBUILD_MODNAME),
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0xba4bcda1, "struct_module" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x7060a772, "s3c2410_gpio_cfgpin" },
	{ 0xbec4672b, "register_chrdev" },
	{ 0xdd132261, "printk" },
	{ 0xfb7d9c45, "__udivsi3" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


/*
* hello.c – The Hello, World! Kernel Module
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*
* hello_init – the init function, called when the module is loaded.
* Returns zero if successfully loaded, nonzero otherwise.
*/
static int hello_init(void)
{
    printk(KERN_ALERT "hello_init\n");
    return 0;
}
/*
* hello_exit – the exit function, called when the module is removed.
*/
static void hello_exit(void)
{
    printk(KERN_ALERT "hello_exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakespeare");
MODULE_DESCRIPTION("A Hello, World Module");


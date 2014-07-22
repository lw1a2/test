/*
* test_proc.c – The test procfs Kernel Module
* work on kenrel 3.5.0
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

struct proc_dir_entry *test;
char content[PAGE_SIZE];

int test_proc_read(char *page, char **start, off_t off,
              int count, int *eof, void *data)
{
    int len;
    // printk(KERN_ALERT "test_proc_read\n");
    len = sprintf(page, "%s", content);
    return len;
}

int test_proc_write(struct file *file, const char __user *buffer,
               unsigned long count, void *data)
{
    // printk(KERN_ALERT "test_proc_write\n");
    memset(content, 0, sizeof(content));
    copy_from_user(content, buffer, count);
    return count;
}

/*
* test_proc_init – the init function, called when the module is loaded.
* Returns zero if successfully loaded, nonzero otherwise.
*/
static int test_proc_init(void)
{
    struct proc_dir_entry *status;
    printk(KERN_ALERT "test_proc_init\n");
    test = proc_mkdir("test", NULL);
    status = create_proc_entry("status", 0644, test);
    status->read_proc = test_proc_read;
    status->write_proc = test_proc_write;
    return 0;
}
/*
* test_proc_exit – the exit function, called when the module is removed.
*/
static void test_proc_exit(void)
{
    printk(KERN_ALERT "test_proc_exit\n");
    remove_proc_entry("status", test);
    remove_proc_entry("test", NULL);
}

module_init(test_proc_init);
module_exit(test_proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("lw1a2");
MODULE_DESCRIPTION("A test procfs module");


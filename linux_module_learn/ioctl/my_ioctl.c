#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define CMD_TEST_0 _IO('A', 0)         // 不需要读写的命令
#define CMD_TEST_1 _IOR('A', 1, int)   // 从内核读取一个int的命令
#define CMD_TEST_2 _IOW('A', 2, int)   // 向内核写入一个int的命令
#define CMD_TEST_3 _IOWR('A', 3, int)  // 读写一个int的命令

int misc_open(struct inode *a, struct file *b)
{
    printk("misc open \n");
    return 0;
}

int misc_release(struct inode *a, struct file *b)
{
    printk("misc file release\n");
    return 0;
}

long misc_ioctl(struct file *fd, unsigned int cmd, unsigned long b)
{
    /*将命令按内容分解，打印出来*/
    printk("cmd type=%c\t nr=%d\t dir=%d\t size=%d\n", _IOC_TYPE(cmd),
           _IOC_NR(cmd), _IOC_DIR(cmd), _IOC_SIZE(cmd));

    switch (cmd)
    {
    case CMD_TEST_0:
        printk("CMD_TEST_0\n");
        break;
    case CMD_TEST_1:
        printk("CMD_TEST_1\n");
        return 1;
        break;
    case CMD_TEST_2:
        printk("CMD_TEST_2 date=%d\n", b);
        break;
    case CMD_TEST_3:
        printk("CMD_TEST_3 date=%ld\n", b);
        return b + 1;
        break;
    }

    return 0;
}

// 文件操作集
struct file_operations misc_fops = {.owner = THIS_MODULE,
                                    .open = misc_open,
                                    .release = misc_release,
                                    .unlocked_ioctl = misc_ioctl};

struct miscdevice misc_dev = {.minor = MISC_DYNAMIC_MINOR,
                              .name = "test_ioctrl",  // 设备节点名
                              .fops = &misc_fops};

static int hello_init(void)
{
    int ret;

    ret = misc_register(&misc_dev);  // 注册杂项设备
    if (ret < 0)
    {
        printk("misc regist failed\n");
        return -1;
    }

    printk("misc regist succeed\n");
    return 0;
}

static void hello_exit(void) { misc_deregister(&misc_dev); }

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("BlackHole");

module_init(hello_init);
module_exit(hello_exit);

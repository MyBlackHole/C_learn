#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/timer.h>

//声明定时器处理函数
static void ta_timer_func(unsigned long dat);  

//定义、初始化定时器，expires参数不必再此初始化，在需要开启的时候再计算节拍
DEFINE_TIMER(taxue_timer, ta_timer_func, 0, 0);

//定义定时器处理函数
static void ta_timer_func(unsigned long dat){
    static int count=0;
    printk("hello timer count=%d\n",count++);
    if(count <= 50){
        //修改定时器，让定时器再次工作
        //节拍设置为当前时间+count*10毫秒
        mod_timer(&taxue_timer, jiffies + msecs_to_jiffies(count*10));
    }else{
        printk("done\n");
    }
}

static int driver_init_timer(void){
    printk("Hello TaXue\n");
    taxue_timer.expires = jiffies + 1*HZ;  //当前节拍+1秒节拍
    add_timer(&taxue_timer);  //向内核注册定时器
    return 0;
}

static void driver_exit_timer(void){
    del_timer(&taxue_timer);    //删除定时器
    printk("platform driver exit!\n");
}


module_init(driver_init_timer);  //模块入口，加载驱动时执行参数内的函数
module_exit(driver_exit_timer);  //模块出口，卸载模块时执行参数内的函数

MODULE_LICENSE("Dual BSD/GPL"); //遵循BSD和GPL开源许可
MODULE_AUTHOR("BlackHole");  //模块作者

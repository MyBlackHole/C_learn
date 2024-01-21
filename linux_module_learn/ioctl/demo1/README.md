# test
```shell
sudo dmesg -w

sudo insmod my_ioctl.ko

[201750.027008] my_ioctl: loading out-of-tree module taints kernel. (修改为 MODULE_LICENSE("GPL v2");)
[201750.027023] my_ioctl: module verification failed: signature and/or required key missing - tainting kernel
[201750.028984] misc regist succeed


crw------- 1 root root 10, 120 Jan 21 08:40 /dev/test_ioctrl
crwxrwxrwx 1 root root 10, 120 Jan 21 08:45 /dev/test_ioctrl (增加权限后 mode)

sudo ../../out/obj/ioctl_learn/app
open success
receive 1 data=1
receive 3 data=102


[300749.549118] misc regist succeed
[300841.270844] misc open
[300841.270879] cmd type=A       nr=0    dir=0   size=0
[300841.270882] CMD_TEST_0
[300841.270883] cmd type=A       nr=1    dir=2   size=4
[300841.270885] CMD_TEST_1
[300841.270897] cmd type=A       nr=2    dir=1   size=4
[300841.270898] CMD_TEST_2 date=99
[300841.270900] cmd type=A       nr=3    dir=3   size=4
[300841.270901] CMD_TEST_3 date=101
[300841.270915] misc file release
```

- 内核直接读取用户层空间地址内存(下面是个好想法)
```c
taskpid = find_get_pid(curpid);
task = pid_task(taskpid, PIDTYPE_PID );
mm = get_task_mm(task);
down_read(&mm->mmap_sem);

// vaddr 虚拟地址
start_vaddr = vaddr;
end_vaddr = 0xC0000000;

while( start_vaddr < end_vaddr){
    u32 end;

    end = (( start_vaddr + PMD_SIZE) & PMD_MASK);

    if( end < start_vaddr || end > end_vaddr)
        end = end_vaddr;

    ret = walk_pgd(start_vaddr, end, mm);
    if(ret != 0){
        printk("ret: %08x \n", ret);
        break;
    }

    start_vaddr = end;

}

up_read(&mm->mmap_sem);

paddr = ret;
kaddr = __va(paddr);
mmput(mm);
```

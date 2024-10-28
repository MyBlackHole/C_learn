```
1. sigprocmask函数提供屏蔽和解除屏蔽信号的功能。
    #include <signal.h>
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

    其中参数 how可设置的参数为：SIG_BLOCK， SIG_UNBLOCK，SIG_SETMASK
    SIG_BLOCK：
        按照参数 set 提供的屏蔽字，屏蔽信号。并将原信号屏蔽保存到oldset中。
    SIG_UNBLOCK：
        按照参数 set 提供的屏蔽字进行信号的解除屏蔽。针对Set中的信号进行解屏。
    SIG_SETMASK:
        按照参数 set 提供的信号设置重新设置系统信号设置。

2. 信号屏蔽与解屏常见实现
    方法一: 
    SIG_BLOCK, SIG_UNBLOCK成对实现
    优点oldset可以不管。

    方法二：
    SIG_BLOCK设置屏蔽，保存原有信号设置。
    SIG_SETMASK重新恢复原有设置。

3. 屏蔽过程中接受到的信号如何处理
    在信号屏蔽过程中，出现的所有被屏蔽的信号，不管发生多少次，
    在信号解除屏蔽后，系统会执行一次被屏蔽信号上的操作。
```

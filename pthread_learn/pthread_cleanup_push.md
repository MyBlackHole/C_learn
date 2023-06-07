# pthread_cleanup_push
函数地址添加到调用线程的清理函数栈顶

注册的顺序是： cleanup_times --> cleanup_minus --> cleanup_add

调用的顺序是： cleanup_add   --> cleanup_minus --> cleanup_times

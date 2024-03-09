sudo insmod workqueue_test.ko

ll /proc/workqueue
Permissions Size User Date Modified Name
.r--r--r--     0 root  9 Mar 23:44   /proc/workqueue

[root@black workqueue]# lvim /proc/workqueue
[root@black workqueue]# echo 1 > /proc/workqueue
[root@black workqueue]#

[ 1670.972613] workqueue_proc_show ,cpu id = 8
[ 1670.973506] work_demo_func ,cpu id = 8,taskname = kworker/8:0
[ 1743.504968] workqueue_proc_store ,work_demo,cpu id = 7
[ 1743.504982] queue work_demo end
[ 1743.505173] work_demo_func ,cpu id = 7,taskname = kworker/7:2

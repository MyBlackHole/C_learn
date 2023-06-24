#! /bin/bash

# 清空 slab cache
echo 2 > /proc/sys/vm/drop_caches
# 调低 soft lockup 的阈值
echo 1 > /proc/sys/kernel/watchdog_thresh

num=0
while true;
do
 ((num++))
 rm -f /tmp/test/$num.tmp > /dev/null
done

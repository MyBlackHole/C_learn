# mount 隔离测试

```shell
# 会话一
sudo ./out/obj/namespace_learn/mount/unshare -m /bin/bash
mkdir /tmp/mount_test/
mount -t tmpfs tmpfs /tmp/mount_test/
root@BlackHole:/tmp# cd mount_test/
root@BlackHole:/tmp/mount_test# touch a b c
root@BlackHole:/tmp/mount_test# ls
a  b  c

# 新建会话二
❯ cd /tmp/mount_test
❯ ls
  /tmp/mount_test                                                                                      at  09:32:12
❯
```

# renameat2

## test

```shell
<!-- xfs 支持 whiteout 都行 -->
touch /opt/aio/Debug/oldfile3 && echo "oldfile3" > /opt/aio/Debug/oldfile3
touch /run/media/black/Data/Documents/c/Debug/oldfile1 && echo "oldfile1" > /run/media/black/Data/Documents/c/Debug/oldfile1
touch /run/media/black/Data/Documents/c/Debug/oldfile2 && echo "oldfile2" > /run/media/black/Data/Documents/c/Debug/oldfile2


<!-- touch /tmp/newfile1 -->
<!-- touch /tmp/newfile2 -->
<!-- touch /tmp/newfile3 -->

xmake run stdio_learn renameat2
```

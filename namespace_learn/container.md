# container 隔离测试
```shell
mkdir -p rootfs/{bin,dev,etc,home,lib/x86_64-linux-gnu,lib64,mnt,opt,proc,root,run,sbin,sys,tmp,usr/bin,var}
cp /usr/bin/sh /usr/bin/ls /usr/bin/mount /usr/bin/cat /usr/bin/ps rootfs/usr/bin/
cp /etc/hosts /etc/hostname /etc/resolv.conf rootfs/etc
cp /lib/x86_64-linux-gnu/libc.so.6 rootfs/lib/x86_64-linux-gnu/
cp /lib64/ld-linux-x86-64.so.2 rootfs/lib64
cp /lib/x86_64-linux-gnu/libselinux.so.1 rootfs/lib/x86_64-linux-gnu/libselinux.so.1
cp /lib/x86_64-linux-gnu/libpcre2-8.so.0 rootfs/lib/x86_64-linux-gnu/libpcre2-8.so.0
cp /lib/x86_64-linux-gnu/libdl.so.2 rootfs/lib/x86_64-linux-gnu/libdl.so.2
cp /lib64/ld-linux-x86-64.so.2 rootfs/lib64/ld-linux-x86-64.so.2
cp /lib/x86_64-linux-gnu/libpthread.so.0 rootfs/lib/x86_64-linux-gnu/libpthread.so.0
cp /lib/x86_64-linux-gnu/libmount.so.1 rootfs/lib/x86_64-linux-gnu/libmount.so.1
cp /lib/x86_64-linux-gnu/libblkid.so.1 rootfs/lib/x86_64-linux-gnu/libblkid.so.1
cp /lib/x86_64-linux-gnu/libselinux.so.1 rootfs/lib/x86_64-linux-gnu/libselinux.so.1
cp /lib/x86_64-linux-gnu/libprocps.so.8 rootfs/lib/x86_64-linux-gnu/libprocps.so.8
cp /lib/x86_64-linux-gnu/libsystemd.so.0 rootfs/lib/x86_64-linux-gnu/libsystemd.so.0
cp /lib/x86_64-linux-gnu/librt.so.1 rootfs/lib/x86_64-linux-gnu/librt.so.1
cp /lib/x86_64-linux-gnu/liblzma.so.5 rootfs/lib/x86_64-linux-gnu/liblzma.so.5
cp /lib/x86_64-linux-gnu/libzstd.so.1 rootfs/lib/x86_64-linux-gnu/libzstd.so.1
cp /lib/x86_64-linux-gnu/liblz4.so.1 rootfs/lib/x86_64-linux-gnu/liblz4.so.1
cp /lib/x86_64-linux-gnu/libgcrypt.so.20 rootfs/lib/x86_64-linux-gnu/libgcrypt.so.20
cp /lib/x86_64-linux-gnu/libgpg-error.so.0 rootfs/lib/x86_64-linux-gnu/libgpg-error.so.0

sudo ./out/obj/namespace_learn/container
```

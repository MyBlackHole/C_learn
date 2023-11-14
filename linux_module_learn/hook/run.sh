make

cat /proc/cmdline
# BOOT_IMAGE=/BOOT/ubuntu_ty4pf5@/vmlinuz-6.2.0-36-generic root=ZFS=rpool/ROOT/ubuntu_ty4pf5 ro quiet splash vt.handoff=1

sudo dmesg -w
# [950849.996627] livepatch: enabling patch 'livepatch_sample'
# [950850.021980] livepatch: 'livepatch_sample': starting patching transition
# [950850.873603] livepatch: 'livepatch_sample': patching complete

# 开启跟踪
sudo bpftrace -e 'kprobe:klp_enable_patch {printf("call klp_enable_patch.\n");}'

sudo insmod livepatch-sample.ko

cat /proc/cmdline
# this has been live patched


sudo rmmod livepatch-sample.ko 
# rmmod: ERROR: Module livepatch_sample is in use


# pwd
/sys/kernel/livepatch
# tree -a
.
└── livepatch_sample
    ├── enabled
    ├── force
    ├── transition
    └── vmlinux
        ├── cmdline_proc_show,1
        └── loadavg_proc_show,1

4 directories, 3 files

echo 0 > livepatch_sample/enabled 
tree -a

sudo rmmod livepatch_sample

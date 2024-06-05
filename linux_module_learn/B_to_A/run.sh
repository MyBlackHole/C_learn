cd ./AAAA/
make

# 需要先编译，原因未知
cd ./BBBB/ 
make

cp ./AAAA/Module.symvers ./BBBB

cd ./BBBB/
make
# 必须 EXPORT_SYMBOL 才可以被其他模块调用


# 测试多个 mod 同名静态对象,使用问题
insmod AAAA.ko
insmod CCCC.ko
# 结论允许的, 非同一模块的同名静态对象可以共存


insmod DDDD.ko
rmmod DDDD.ko
[88071.938220] aaaa_exit
[88071.938266] invalid opcode: 0000 [#1] SMP NOPTI
[88071.938297] CPU: 3 PID: 418567 Comm: rmmod Tainted: P           OE    --------- -  - 4.19.0-240.23.11.el8_2.bclinux.x86_64 #1
[88071.938333] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 11/12/2020
[88071.938366] RIP: 0010:aaaa_exit+0xc/0x1000 [DDDD]
[88071.938389] Code: Bad RIP value.
[88071.938402] RSP: 0018:ffffb2e706db7ee0 EFLAGS: 00010246
[88071.938420] RAX: 0000000000000009 RBX: ffffffffc0d19000 RCX: 0000000000000000
[88071.938441] RDX: 0000000000000000 RSI: ffff97def3cd6908 RDI: ffff97def3cd6908
[88071.938467] RBP: ffffb2e706db7f58 R08: 00000000000006c5 R09: 0000000000000004
[88071.938502] R10: 0000000000000000 R11: 0000000000000001 R12: 0000000000000000
[88071.938524] R13: 0000000000000000 R14: 0000000000000000 R15: 0000000000000000
[88071.938550] FS:  00007f353b3f4740(0000) GS:ffff97def3cc0000(0000) knlGS:0000000000000000
[88071.938580] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[88071.938602] CR2: ffffffffc0d16fe2 CR3: 00000002a323e006 CR4: 00000000007606e0
[88071.938652] PKRU: 55555554
[88071.938664] Call Trace:
[88071.938682]  __x64_sys_delete_module+0x139/0x280
[88071.938700]  do_syscall_64+0x5b/0x1a0
[88071.938721]  entry_SYSCALL_64_after_hwframe+0x65/0xca
[88071.938738] RIP: 0033:0x7f353a3dc7db
[88071.938752] Code: 73 01 c3 48 8b 0d ad f6 2b 00 f7 d8 64 89 01 48 83 c8 ff c3 66 2e 0f 1f 84 00 00 00 00 00 90 f3 0f 1e fa b8 b0 00 00 00 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d 7d f6 2b 00 f7 d8 64 89 01 48
[88071.938815] RSP: 002b:00007fff05a2c318 EFLAGS: 00000206 ORIG_RAX: 00000000000000b0
[88071.938838] RAX: ffffffffffffffda RBX: 000055f0c30f2750 RCX: 00007f353a3dc7db
[88071.938858] RDX: 000000000000000a RSI: 0000000000000800 RDI: 000055f0c30f27b8
[88071.938887] RBP: 0000000000000000 R08: 00007fff05a2b291 R09: 0000000000000000
[88071.938908] R10: 00007f353a44e8e0 R11: 0000000000000206 R12: 00007fff05a2c540
[88071.938930] R13: 00007fff05a2d20b R14: 000055f0c30f22a0 R15: 000055f0c30f2750
[88071.938953] Modules linked in: DDDD(OE-) vsock_loopback vmw_vsock_virtio_transport_common vmw_vsock_vmci_transport vsock zfs(POE) intel_rapl_msr intel_rapl_common isst_if_mbox_msr isst_if_common nfit libnvdimm crct10dif_pclmul crc32_pclmul mousedev ghash_clmulni_intel pcbc aesni_intel crypto_simd glue_helper psmouse vmw_balloon intel_rapl_perf pcspkr i2c_piix4 vmw_vmci icp(POE) zlua(POE) zcommon(POE) zunicode(POE) znvpair(POE) nfsd auth_rpcgss zavl(POE) nfs_acl lockd grace spl(OE) sunrpc ip_tables xfs libcrc32c sr_mod cdrom sd_mod sg ata_generic crc32c_intel vmwgfx serio_raw drm_kms_helper syscopyarea sysfillrect sysimgblt fb_sys_fops vmxnet3 ttm drm vmw_pvscsi ahci libahci ata_piix dm_mirror dm_region_hash dm_log dm_mod
[88071.939297] ---[ end trace 338ab53195c67bb0 ]---
[88071.939314] RIP: 0010:aaaa_exit+0xc/0x1000 [DDDD]
[88071.939334] Code: Bad RIP value.
[88071.939347] RSP: 0018:ffffb2e706db7ee0 EFLAGS: 00010246
[88071.939368] RAX: 0000000000000009 RBX: ffffffffc0d19000 RCX: 0000000000000000
[88071.939396] RDX: 0000000000000000 RSI: ffff97def3cd6908 RDI: ffff97def3cd6908
[88071.939423] RBP: ffffb2e706db7f58 R08: 00000000000006c5 R09: 0000000000000004
[88071.939442] R10: 0000000000000000 R11: 0000000000000001 R12: 0000000000000000
[88071.939463] R13: 0000000000000000 R14: 0000000000000000 R15: 0000000000000000
[88071.939488] FS:  00007f353b3f4740(0000) GS:ffff97def3cc0000(0000) knlGS:0000000000000000
[88071.939516] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[88071.940427] CR2: ffffffffc0d16fe2 CR3: 00000002a323e006 CR4: 00000000007606e0
[88071.941285] PKRU: 55555554
[88071.942058] Kernel panic - not syncing: Fatal exception

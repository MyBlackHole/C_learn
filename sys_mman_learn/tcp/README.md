```shell
❯ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 23         black      600        524288     2          dest
0x6600af68 26         black      0          4096       0


❯ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 23         black      600        524288     2          dest
0x6600af68 26         black      0          4096       0
0x66210001 30         black      0          4096       0

❯ ipcrm -m 26
❯ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 23         black      600        524288     2          dest
0x66210001 30         black      0          4096       0
```

```shell
------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status
0x00000000 23         black      600        524288     2          dest
0x66210001 30         black      0          4096       0
0x00000000 35         black      666        4096       1          dest
```

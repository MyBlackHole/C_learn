❯ ./out/obj/dome/change_pid_mem/app
foo before modify: Hello proc-1 world
./change  1480269  0x7ffe686fb330  19
Press any key
c
foo after modify: Hello proc-2 world

❯ sudo ./out/obj/dome/change_pid_mem/change 1480269  0x7ffe686fb330  19
opening /proc/1480269/mem, address is 0x7ffe686fb330
String at 0x7ffe686fb330 in process 1480269 is:
  Hello proc-1 world

Now, this string is modified

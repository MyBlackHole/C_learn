/*
 *  linux/kernel/keyboard.S
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 *	Thanks to Alfred Leung for US keyboard patches
 *		Wolfgang Thiel for German keyboard patches
 *		Marc Corsini for the French keyboard
 */
/*
 *	感谢 Alfred Leung 添加了 US 键盘补丁程序；
 *		Wolfgang Thiel 添加了德语键盘补丁程序；
 *		Marc Corsini 添加了法文键盘补丁程序。
 */

/* KBD_FINNISH for Finnish keyboards
 * KBD_US for US-type
 * KBD_GR for German keyboards
 * KBD_FR for Frech keyboard
 */
/*
 * KBD_FINNISH 是芬兰键盘。
 * KBD_US 是美式键盘。
 * KBD_GR 是德式键盘。
 * KBD_FR 是法式键盘。
 */


#define KBD_FINNISH    // 定义使用的键盘类型。用于后面选择采用的字符映射码表。

.text
.globl _keyboard_interrupt    // 申明为全局变量，用于在初始化时设置键盘中断描述符。

/*
 * 以下这些用于读键盘操作。
 */
/*
 * these are for the keyboard read functions
 */
// size 是键盘缓冲区（缓冲队列）长度（字节数）。
/* 值必须是 2 的次方！并且与 tty_io.c 中的值匹配!!!! */
size	= 1024		/* must be a power of two ! And MUST be the same
			   as in tty_io.c !!!! */
// 以下是键盘缓冲队列数据结构 tty_queue 中各字段的偏移量（include/linux/tty.h，第 22 行）。
head = 4    // 缓冲区头指针字段在 tty_queue 结构中的偏移。
tail = 8    // 缓冲区尾指针字段偏移。
proc_list = 12    // 等待该缓冲队列的进程字段偏移。
buf = 16    // 缓冲区字段偏移。

// 在本程序中使用了 3 个标志字节。mode 是键盘特殊键(ctrl、alt 或 caps)的按下状态标志；
// leds 是用于表示键盘指示灯的状态标志。 e0 是当收到扫描码 0xe0 或 0xe1 时设置的标志。
// 每个字节标志中各位的含义见如下说明：
//      (1) mode 是键盘特殊键的按下状态标志。
//      表示大小写转换键(caps)、交换键(alt)、控制键(ctrl)和换档键(shift)的状态。
//          位 7 caps 键按下； 位 3 右 ctrl 键按下；
//          位 6 caps 键的状态； 位 2 左 ctrl 键按下；
//          位 5 右 alt 键按下； 位 1 右 shift 键按下；
//          位 4 左 alt 键按下； 位 0 左 shift 键按下。
//      (2) leds 是用于表示键盘指示灯的状态标志。即表示数字锁定键（num-lock）、大小写转换
//      键（caps-lock）和滚动锁定键（scroll-lock）的 LED 发光管状态。
//          位 7-3 全 0 不用； 位 1 num-lock（初始置 1，即数字锁定键发光管亮）；
//          位 2 caps-lock； 位 0 scroll-lock。
//      (3) e0 是扫描前导码标志。当扫描码是 0xe0 或 0xe1 时，置该标志。表示其后还跟随着 1 个或 2
//      个字符扫描码。若收到扫描码 0xe0 则意味着还有一个字符跟随其后；若收到扫描码 0xe1 则表示
//      后面还跟随着 2 个字符。参见程序列表后说明。e0 标志可用于区别键盘上两个相同的键或同一按
//      键上不同的功能，若 e0 标志是 1，则表示两个相同按键中右边的一个按键，或者是数字小键盘上
//      方向键的功能。
//          位 1 =1 收到 0xe1 标志； 位 0 =1 收到 0xe0 标志。

mode:	.byte 0		/* caps, alt, ctrl and shift mode */
leds:	.byte 2		/* num-lock, caps, scroll-lock mode (nom-lock on) */
e0:	.byte 0

/*
 *  con_int is the real interrupt routine that reads the
 *  keyboard scan-code and converts it into the appropriate
 *  ascii character(s).
 */
/*
 * con_int 是实际的中断处理子程序，用于读键盘扫描码并将其转换
 * 成相应的 ascii 字符。[ 注：这段英文注释已过时。]
 */
//// 键盘中断处理程序入口点。
// 当键盘控制器接收到用户的一个按键操作时，就会向中断控制器发出一键盘中断请求信号 IRQ1。
// 当 CPU 响应该请求时就会执行键盘中断处理程序。该中断处理程序会从键盘控制器端口（0x60）
// 读入按键扫描码，并调用对应的扫描码子程序进行处理。
// 首先从端口 0x60 读取当前按键的扫描码，然后判断该扫描码是否是 0xe0 或 0xe1。如果是的话
// 就立刻对键盘控制器作出应答，并向中断控制器发送中断结束（EOI）信号，以允许键盘控制器
// 能继续产生中断信号，从而让我们来接收后续的字符。 如果接收到的扫描码不是这两个特殊扫
// 描码，我们就根据扫描码值调用按键跳转表 key_table 中相应按键处理子程序，把扫描码对应
// 的字符放入读字符缓冲队列 read_q 中。然后，在对键盘控制器作出应答并发送 EOI 信号之后，
// 调用函数 do_tty_interrupt()（实际上是调用 copy_to_cooked()）把 read_q 中的字符经过处理
// 后放到 secondary 辅助队列中。
_keyboard_interrupt:
	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	push %ds
	push %es
	movl $0x10,%eax    // 将 ds、es 段寄存器置为内核数据段。
	mov %ax,%ds
	mov %ax,%es
	movl _blankinterval,%eax
	movl %eax,_blankcount    // 预置黑屏时间计数值为 blankinterval(滴答数)。
	xorl %eax,%eax		/* %eax is scan code */    /* eax 中是扫描码 */
	inb $0x60,%al    // 读取扫描码al。
	cmpb $0xe0,%al    // 扫描码是 0xe0 吗？若是则跳转到设置 e0 标志代码处。
	je set_e0
	cmpb $0xe1,%al    // 扫描码是 0xe1 吗？若是则跳转到设置 e1 标志代码处。
	je set_e1
	call key_table(,%eax,4)     // 调用键处理程序 key_table + eax*4(参见 567 行)。
	movb $0,e0    // 返回之后复位 e0 标志。

// 下面这段代码(120-130 行)针对使用 8255A 的 PC 标准键盘电路进行硬件复位处理。端口 0x61
// 是 8255A 输出口 B 的地址，该输出端口的第 7 位(PB7)用于禁止和允许对键盘数据的处理。
// 这段程序用于对收到的扫描码做出应答。方法是首先禁止键盘，然后立刻重新允许键盘工作。
e0_e1:	inb $0x61,%al    // 取 PPI 端口 B 状态，其位 7 用于允许/禁止（0/1）键盘。
	jmp 1f    // 延迟一会。
1:	jmp 1f
1:	orb $0x80,%al    // al 位 7 置位（禁止键盘工作）。
	jmp 1f
1:	jmp 1f
1:	outb %al,$0x61      // 使 PPI PB7 位置位。
	jmp 1f
1:	jmp 1f
1:	andb $0x7F,%al      // al 位 7 复位。
	outb %al,$0x61      // 使 PPI PB7 位复位（允许键盘工作）。
	movb $0x20,%al      // 向 8259 中断芯片发送 EOI(中断结束)信号。
	outb %al,$0x20
	pushl $0        // 控制台 tty 号=0，作为参数入栈。
	call _do_tty_interrupt      // 将收到数据转换成规范模式并存放在规范字符缓冲队列中。
	addl $4,%esp        // 丢弃入栈的参数，弹出保留的寄存器，并中断返回。
	pop %es
	pop %ds
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret
set_e0:	movb $1,e0      // 收到扫描前导码 0xe0 时，设置 e0 标志的位 0。
	jmp e0_e1
set_e1:	movb $2,e0      // 收到扫描前导码 0xe1 时，设置 e0 标志的位 1。
	jmp e0_e1

/*
 * This routine fills the buffer with max 8 bytes, taken from
 * %ebx:%eax. (%edx is high). The bytes are written in the
 * order %al,%ah,%eal,%eah,%bl,%bh ... until %eax is zero.
 */
/*
* 下面该子程序把 ebx:eax 中的最多 8 个字符添入缓冲队列中。（ebx 是
* 高字）所写入字符的顺序是 al,ah,eal,eah,bl,bh...直到 eax 等于 0。
*/
// 首先从缓冲队列地址表 table_list（tty_io.c，81 行）取控制台的读缓冲队列 read_q 地址。
// 然后把 al 寄存器中的字符复制到读队列头指针处并把头指针前移 1 字节位置。若头指针移出
// 读缓冲区的末端，就让其回绕到缓冲区开始处。 然后再看看此时缓冲队列是否已满，即比较
// 一下队列头指针是否与尾指针相等（相等表示满）。 如果已满，就把 ebx:eax 中可能还有的
// 其余字符全部抛弃掉。如果缓冲区还未满，就把 ebx:eax 中数据联合右移 8 个比特（即把 ah
// 值移到 al、blah、bhbl），然后重复上面对 al 的处理过程。直到所有字符都处理完后，
// 就保存当前头指针值，再检查一下是否有进程等待着读队列，如果有就唤醒之。
put_queue:
	pushl %ecx
	pushl %edx
	movl _table_list,%edx		# read-queue for console
	movl head(%edx),%ecx
1:	movb %al,buf(%edx,%ecx)
	incl %ecx
	andl $size-1,%ecx
	cmpl tail(%edx),%ecx		# buffer full - discard everything
	je 3f
	shrdl $8,%ebx,%eax
	je 2f
	shrl $8,%ebx
	jmp 1b
2:	movl %ecx,head(%edx)
	movl proc_list(%edx),%ecx
	testl %ecx,%ecx
	je 3f
	movl $0,(%ecx)
3:	popl %edx
	popl %ecx
	ret

ctrl:	movb $0x04,%al
	jmp 1f
alt:	movb $0x10,%al
1:	cmpb $0,e0
	je 2f
	addb %al,%al
2:	orb %al,mode
	ret
unctrl:	movb $0x04,%al
	jmp 1f
unalt:	movb $0x10,%al
1:	cmpb $0,e0
	je 2f
	addb %al,%al
2:	notb %al
	andb %al,mode
	ret

lshift:
	orb $0x01,mode
	ret
unlshift:
	andb $0xfe,mode
	ret
rshift:
	orb $0x02,mode
	ret
unrshift:
	andb $0xfd,mode
	ret

caps:	testb $0x80,mode
	jne 1f
	xorb $4,leds
	xorb $0x40,mode
	orb $0x80,mode
set_leds:
	call kb_wait
	movb $0xed,%al		/* set leds command */
	outb %al,$0x60
	call kb_wait
	movb leds,%al
	outb %al,$0x60
	ret
uncaps:	andb $0x7f,mode
	ret
scroll:
	testb $0x03,mode
	je 1f
	call _show_mem
	jmp 2f
1:	call _show_state
2:	xorb $1,leds
	jmp set_leds
num:	xorb $2,leds
	jmp set_leds

/*
 *  curosr-key/numeric keypad cursor keys are handled here.
 *  checking for numeric keypad etc.
 */
cursor:
	subb $0x47,%al
	jb 1f
	cmpb $12,%al
	ja 1f
	jne cur2		/* check for ctrl-alt-del */
	testb $0x0c,mode
	je cur2
	testb $0x30,mode
	jne reboot
cur2:	cmpb $0x01,e0		/* e0 forces cursor movement */
	je cur
	testb $0x02,leds	/* not num-lock forces cursor */
	je cur
	testb $0x03,mode	/* shift forces cursor */
	jne cur
	xorl %ebx,%ebx
	movb num_table(%eax),%al
	jmp put_queue
1:	ret

cur:	movb cur_table(%eax),%al
	cmpb $'9,%al
	ja ok_cur
	movb $'~,%ah
ok_cur:	shll $16,%eax
	movw $0x5b1b,%ax
	xorl %ebx,%ebx
	jmp put_queue

#if defined(KBD_FR)
num_table:
	.ascii "789 456 1230."
#else
num_table:
	.ascii "789 456 1230,"
#endif
cur_table:
	.ascii "HA5 DGC YB623"

/*
 * this routine handles function keys
 */
func:
	subb $0x3B,%al
	jb end_func
	cmpb $9,%al
	jbe ok_func
	subb $18,%al
	cmpb $10,%al
	jb end_func
	cmpb $11,%al
	ja end_func
ok_func:
	testb $0x10,mode
	jne alt_func
	cmpl $4,%ecx		/* check that there is enough room */
	jl end_func
	movl func_table(,%eax,4),%eax
	xorl %ebx,%ebx
	jmp put_queue
alt_func:
	pushl %eax
	call _change_console
	popl %eax
end_func:
	ret

/*
 * function keys send F1:'esc [ [ A' F2:'esc [ [ B' etc.
 */
func_table:
	.long 0x415b5b1b,0x425b5b1b,0x435b5b1b,0x445b5b1b
	.long 0x455b5b1b,0x465b5b1b,0x475b5b1b,0x485b5b1b
	.long 0x495b5b1b,0x4a5b5b1b,0x4b5b5b1b,0x4c5b5b1b

#if	defined(KBD_FINNISH)
key_map:
	.byte 0,27
	.ascii "1234567890+'"
	.byte 127,9
	.ascii "qwertyuiop}"
	.byte 0,13,0
	.ascii "asdfghjkl|{"
	.byte 0,0
	.ascii "'zxcvbnm,.-"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '<
	.fill 10,1,0

shift_map:
	.byte 0,27
	.ascii "!\"#$%&/()=?`"
	.byte 127,9
	.ascii "QWERTYUIOP]^"
	.byte 13,0
	.ascii "ASDFGHJKL\\["
	.byte 0,0
	.ascii "*ZXCVBNM;:_"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '>
	.fill 10,1,0

alt_map:
	.byte 0,0
	.ascii "\0@\0$\0\0{[]}\\\0"
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte '~,13,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0,0,0		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte 0,0,0,0,0		/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '|
	.fill 10,1,0

#elif defined(KBD_US)

key_map:
	.byte 0,27
	.ascii "1234567890-="
	.byte 127,9
	.ascii "qwertyuiop[]"
	.byte 13,0
	.ascii "asdfghjkl;'"
	.byte '`,0
	.ascii "\\zxcvbnm,./"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '<
	.fill 10,1,0


shift_map:
	.byte 0,27
	.ascii "!@#$%^&*()_+"
	.byte 127,9
	.ascii "QWERTYUIOP{}"
	.byte 13,0
	.ascii "ASDFGHJKL:\""
	.byte '~,0
	.ascii "|ZXCVBNM<>?"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '>
	.fill 10,1,0

alt_map:
	.byte 0,0
	.ascii "\0@\0$\0\0{[]}\\\0"
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte '~,13,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0,0,0		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte 0,0,0,0,0		/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '|
	.fill 10,1,0

#elif defined(KBD_GR)

key_map:
	.byte 0,27
	.ascii "1234567890\\'"
	.byte 127,9
	.ascii "qwertzuiop@+"
	.byte 13,0
	.ascii "asdfghjkl[]^"
	.byte 0,'#
	.ascii "yxcvbnm,.-"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '<
	.fill 10,1,0


shift_map:
	.byte 0,27
	.ascii "!\"#$%&/()=?`"
	.byte 127,9
	.ascii "QWERTZUIOP\\*"
	.byte 13,0
	.ascii "ASDFGHJKL{}~"
	.byte 0,''
	.ascii "YXCVBNM;:_"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '>
	.fill 10,1,0

alt_map:
	.byte 0,0
	.ascii "\0@\0$\0\0{[]}\\\0"
	.byte 0,0
	.byte '@,0,0,0,0,0,0,0,0,0,0
	.byte '~,13,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0,0,0		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte 0,0,0,0,0		/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '|
	.fill 10,1,0


#elif defined(KBD_FR)

key_map:
	.byte 0,27
	.ascii "&{\"'(-}_/@)="
	.byte 127,9
	.ascii "azertyuiop^$"
	.byte 13,0
	.ascii "qsdfghjklm|"
	.byte '`,0,42		/* coin sup gauche, don't know, [*|mu] */
	.ascii "wxcvbn,;:!"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '<
	.fill 10,1,0

shift_map:
	.byte 0,27
	.ascii "1234567890]+"
	.byte 127,9
	.ascii "AZERTYUIOP<>"
	.byte 13,0
	.ascii "QSDFGHJKLM%"
	.byte '~,0,'#
	.ascii "WXCVBN?./\\"
	.byte 0,'*,0,32		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte '-,0,0,0,'+	/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '>
	.fill 10,1,0

alt_map:
	.byte 0,0
	.ascii "\0~#{[|`\\^@]}"
	.byte 0,0
	.byte '@,0,0,0,0,0,0,0,0,0,0
	.byte '~,13,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0
	.byte 0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0,0,0		/* 36-39 */
	.fill 16,1,0		/* 3A-49 */
	.byte 0,0,0,0,0		/* 4A-4E */
	.byte 0,0,0,0,0,0,0	/* 4F-55 */
	.byte '|
	.fill 10,1,0

#else
#error "KBD-type not defined"
#endif
/*
 * do_self handles "normal" keys, ie keys that don't change meaning
 * and which have just one character returns.
 */
do_self:
	lea alt_map,%ebx
	testb $0x20,mode		/* alt-gr */
	jne 1f
	lea shift_map,%ebx
	testb $0x03,mode
	jne 1f
	lea key_map,%ebx
1:	movb (%ebx,%eax),%al
	orb %al,%al
	je none
	testb $0x4c,mode		/* ctrl or caps */
	je 2f
	cmpb $'a,%al
	jb 2f
	cmpb $'},%al
	ja 2f
	subb $32,%al
2:	testb $0x0c,mode		/* ctrl */
	je 3f
	cmpb $64,%al
	jb 3f
	cmpb $64+32,%al
	jae 3f
	subb $64,%al
3:	testb $0x10,mode		/* left alt */
	je 4f
	orb $0x80,%al
4:	andl $0xff,%eax
	xorl %ebx,%ebx
	call put_queue
none:	ret

/*
 * minus has a routine of it's own, as a 'E0h' before
 * the scan code for minus means that the numeric keypad
 * slash was pushed.
 */
minus:	cmpb $1,e0
	jne do_self
	movl $'/,%eax
	xorl %ebx,%ebx
	jmp put_queue

/*
 * This table decides which routine to call when a scan-code has been
 * gotten. Most routines just call do_self, or none, depending if
 * they are make or break.
 */
key_table:
	.long none,do_self,do_self,do_self	/* 00-03 s0 esc 1 2 */
	.long do_self,do_self,do_self,do_self	/* 04-07 3 4 5 6 */
	.long do_self,do_self,do_self,do_self	/* 08-0B 7 8 9 0 */
	.long do_self,do_self,do_self,do_self	/* 0C-0F + ' bs tab */
	.long do_self,do_self,do_self,do_self	/* 10-13 q w e r */
	.long do_self,do_self,do_self,do_self	/* 14-17 t y u i */
	.long do_self,do_self,do_self,do_self	/* 18-1B o p } ^ */
	.long do_self,ctrl,do_self,do_self	/* 1C-1F enter ctrl a s */
	.long do_self,do_self,do_self,do_self	/* 20-23 d f g h */
	.long do_self,do_self,do_self,do_self	/* 24-27 j k l | */
	.long do_self,do_self,lshift,do_self	/* 28-2B { para lshift , */
	.long do_self,do_self,do_self,do_self	/* 2C-2F z x c v */
	.long do_self,do_self,do_self,do_self	/* 30-33 b n m , */
	.long do_self,minus,rshift,do_self	/* 34-37 . - rshift * */
	.long alt,do_self,caps,func		/* 38-3B alt sp caps f1 */
	.long func,func,func,func		/* 3C-3F f2 f3 f4 f5 */
	.long func,func,func,func		/* 40-43 f6 f7 f8 f9 */
	.long func,num,scroll,cursor		/* 44-47 f10 num scr home */
	.long cursor,cursor,do_self,cursor	/* 48-4B up pgup - left */
	.long cursor,cursor,do_self,cursor	/* 4C-4F n5 right + end */
	.long cursor,cursor,cursor,cursor	/* 50-53 dn pgdn ins del */
	.long none,none,do_self,func		/* 54-57 sysreq ? < f11 */
	.long func,none,none,none		/* 58-5B f12 ? ? ? */
	.long none,none,none,none		/* 5C-5F ? ? ? ? */
	.long none,none,none,none		/* 60-63 ? ? ? ? */
	.long none,none,none,none		/* 64-67 ? ? ? ? */
	.long none,none,none,none		/* 68-6B ? ? ? ? */
	.long none,none,none,none		/* 6C-6F ? ? ? ? */
	.long none,none,none,none		/* 70-73 ? ? ? ? */
	.long none,none,none,none		/* 74-77 ? ? ? ? */
	.long none,none,none,none		/* 78-7B ? ? ? ? */
	.long none,none,none,none		/* 7C-7F ? ? ? ? */
	.long none,none,none,none		/* 80-83 ? br br br */
	.long none,none,none,none		/* 84-87 br br br br */
	.long none,none,none,none		/* 88-8B br br br br */
	.long none,none,none,none		/* 8C-8F br br br br */
	.long none,none,none,none		/* 90-93 br br br br */
	.long none,none,none,none		/* 94-97 br br br br */
	.long none,none,none,none		/* 98-9B br br br br */
	.long none,unctrl,none,none		/* 9C-9F br unctrl br br */
	.long none,none,none,none		/* A0-A3 br br br br */
	.long none,none,none,none		/* A4-A7 br br br br */
	.long none,none,unlshift,none		/* A8-AB br br unlshift br */
	.long none,none,none,none		/* AC-AF br br br br */
	.long none,none,none,none		/* B0-B3 br br br br */
	.long none,none,unrshift,none		/* B4-B7 br br unrshift br */
	.long unalt,none,uncaps,none		/* B8-BB unalt br uncaps br */
	.long none,none,none,none		/* BC-BF br br br br */
	.long none,none,none,none		/* C0-C3 br br br br */
	.long none,none,none,none		/* C4-C7 br br br br */
	.long none,none,none,none		/* C8-CB br br br br */
	.long none,none,none,none		/* CC-CF br br br br */
	.long none,none,none,none		/* D0-D3 br br br br */
	.long none,none,none,none		/* D4-D7 br br br br */
	.long none,none,none,none		/* D8-DB br ? ? ? */
	.long none,none,none,none		/* DC-DF ? ? ? ? */
	.long none,none,none,none		/* E0-E3 e0 e1 ? ? */
	.long none,none,none,none		/* E4-E7 ? ? ? ? */
	.long none,none,none,none		/* E8-EB ? ? ? ? */
	.long none,none,none,none		/* EC-EF ? ? ? ? */
	.long none,none,none,none		/* F0-F3 ? ? ? ? */
	.long none,none,none,none		/* F4-F7 ? ? ? ? */
	.long none,none,none,none		/* F8-FB ? ? ? ? */
	.long none,none,none,none		/* FC-FF ? ? ? ? */

/*
 * kb_wait waits for the keyboard controller buffer to empty.
 * there is no timeout - if the buffer doesn't empty, we hang.
 */
kb_wait:
	pushl %eax
1:	inb $0x64,%al
	testb $0x02,%al
	jne 1b
	popl %eax
	ret
/*
 * This routine reboots the machine by asking the keyboard
 * controller to pulse the reset-line low.
 */
reboot:
	call kb_wait
	movw $0x1234,0x472	/* don't do memory check */
	movb $0xfc,%al		/* pulse reset and A20 low */
	outb %al,$0x64
die:	jmp die

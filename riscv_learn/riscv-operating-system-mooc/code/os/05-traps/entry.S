# save all General-Purpose(GP) registers to context
# struct context *base = &ctx_task;
# base->ra = ra;
# ......
.macro reg_save base
	sw ra, 0(\base)
	sw sp, 4(\base)
	sw gp, 8(\base)
	sw tp, 12(\base)
	sw t0, 16(\base)
	sw t1, 20(\base)
	sw t2, 24(\base)
	sw s0, 28(\base)
	sw s1, 32(\base)
	sw a0, 36(\base)
	sw a1, 40(\base)
	sw a2, 44(\base)
	sw a3, 48(\base)
	sw a4, 52(\base)
	sw a5, 56(\base)
	sw a6, 60(\base)
	sw a7, 64(\base)
	sw s2, 68(\base)
	sw s3, 72(\base)
	sw s4, 76(\base)
	sw s5, 80(\base)
	sw s6, 84(\base)
	sw s7, 88(\base)
	sw s8, 92(\base)
	sw s9, 96(\base)
	sw s10, 100(\base)
	sw s11, 104(\base)
	sw t3, 108(\base)
	sw t4, 112(\base)
	sw t5, 116(\base)
	# we don't save t6 here, due to we have used
	# it as base, we have to save t6 in an extra step
	# outside of reg_save
.endm

# restore all General-Purpose(GP) registers from the context
# struct context *base = &ctx_task;
# ra = base->ra;
# ......
.macro reg_restore base
	lw ra, 0(\base)
	lw sp, 4(\base)
	lw gp, 8(\base)
	lw tp, 12(\base)
	lw t0, 16(\base)
	lw t1, 20(\base)
	lw t2, 24(\base)
	lw s0, 28(\base)
	lw s1, 32(\base)
	lw a0, 36(\base)
	lw a1, 40(\base)
	lw a2, 44(\base)
	lw a3, 48(\base)
	lw a4, 52(\base)
	lw a5, 56(\base)
	lw a6, 60(\base)
	lw a7, 64(\base)
	lw s2, 68(\base)
	lw s3, 72(\base)
	lw s4, 76(\base)
	lw s5, 80(\base)
	lw s6, 84(\base)
	lw s7, 88(\base)
	lw s8, 92(\base)
	lw s9, 96(\base)
	lw s10, 100(\base)
	lw s11, 104(\base)
	lw t3, 108(\base)
	lw t4, 112(\base)
	lw t5, 116(\base)
	lw t6, 120(\base)
.endm

# Something to note about save/restore:
# - We use mscratch to hold a pointer to context of previous task
# - We use t6 as the 'base' for reg_save/reg_restore, because it is the
#   very bottom register (x31) and would not be overwritten during loading.

.text

# interrupts and exceptions while in machine mode come here.
.globl trap_vector
# the trap vector base address must always be aligned on a 4-byte boundary
.align 4
trap_vector:
	# save context(registers).
  # t6 是 下一个task上下文指针
  # 读到 t6 把 t6 写入
	csrrw	t6, mscratch, t6	# swap t6 and mscratch
  # 保存当前task上下文
	reg_save t6

	# Save the actual t6 register, which we swapped into
	# mscratch
  # 把当前任务上下文地址赋值给 t6 的 t6寄存器
	mv	t5, t6		# t5 points to the context of current task
	csrr	t6, mscratch	# read t6 back from mscratch
	sw	t6, 120(t5)	# save t6 with t5 as base

	# Restore the context pointer into mscratch
  # 恢复到上一个任务 ????
	csrw	mscratch, t5

	# call the C trap handler in trap.c
  # 读取发生异常的指令地址
	csrr	a0, mepc
  # 读取异常种类
	csrr	a1, mcause
	call	trap_handler

	# trap_handler will return the return address via a0.
  # 读取返回值到存储发生异常指令地址的寄存器
	csrw	mepc, a0

	# restore context(registers).
  # 读取当前task上下文指针
	csrr	t6, mscratch
  # 恢复现场
	reg_restore t6

	# return to whatever we were doing before trap.
  # 返回mepc寄存器指向地址
	mret

# void switch_to(struct context *next);
# a0: pointer to the context of the next task
.globl switch_to
.align 4
switch_to:
	csrrw	t6, mscratch, t6	# swap t6 and mscratch
	beqz	t6, 1f			# Notice: previous task may be NULL
	reg_save t6			# save context of prev task

	# Save the actual t6 register, which we swapped into
	# mscratch
	mv	t5, t6		# t5 points to the context of current task
	csrr	t6, mscratch	# read t6 back from mscratch
	sw	t6, 120(t5)	# save t6 with t5 as base

1:
	# switch mscratch to point to the context of the next task
	csrw	mscratch, a0

	# Restore all GP registers
	# Use t6 to point to the context of the new task
	mv	t6, a0
	reg_restore t6

	# Do actual context switching.
	ret

.end


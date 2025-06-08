	.file	"main.c"
	.text
	.globl	mul
	.type	mul, @function
mul:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	mul, .-mul
	.globl	sum
	.type	sum, @function
sum:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$56, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	%edx, -44(%rbp)
	movl	%ecx, -48(%rbp)
	movl	%r8d, -52(%rbp)
	movl	%r9d, -56(%rbp)
	movl	-40(%rbp), %edx
	movl	-36(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	mul
	movl	%eax, -24(%rbp)
	movl	-36(%rbp), %eax
	subl	-40(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-24(%rbp), %edx
	movl	-44(%rbp), %eax
	addl	%eax, %edx
	movl	-48(%rbp), %eax
	addl	%eax, %edx
	movl	-52(%rbp), %eax
	addl	%eax, %edx
	movl	-56(%rbp), %eax
	addl	%eax, %edx
	movl	16(%rbp), %eax
	addl	%eax, %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	sum, .-sum
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	$1, -52(%rbp)
	movl	$2, -48(%rbp)
	movl	$3, -44(%rbp)
	movl	$4, -40(%rbp)
	movl	$5, -36(%rbp)
	movl	$6, -32(%rbp)
	movl	$7, -28(%rbp)
	movl	$8, -24(%rbp)
	movl	-52(%rbp), %edx
	movl	-48(%rbp), %eax
	addl	%eax, %edx
	movl	-44(%rbp), %eax
	addl	%eax, %edx
	movl	-40(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -20(%rbp)
	movl	$4, -16(%rbp)
	movl	$8, -12(%rbp)
	movl	$8, -8(%rbp)
	movl	-32(%rbp), %r9d
	movl	-36(%rbp), %r8d
	movl	-40(%rbp), %ecx
	movl	-44(%rbp), %edx
	movl	-48(%rbp), %esi
	movl	-52(%rbp), %eax
	movl	-24(%rbp), %edi
	pushq	%rdi
	movl	-28(%rbp), %edi
	pushq	%rdi
	movl	%eax, %edi
	call	sum
	addq	$16, %rsp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.1.1 20250425"
	.section	.note.GNU-stack,"",@progbits

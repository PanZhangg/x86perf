	.file	"example1.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	trace_cpu_time_now
	.type	trace_cpu_time_now, @function
trace_cpu_time_now:
.LFB38:
	.cfi_startproc
#APP
# 9 "example1.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	movl	%eax, %eax
	addq	%rdx, %rax
	ret
	.cfi_endproc
.LFE38:
	.size	trace_cpu_time_now, .-trace_cpu_time_now
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	convert_RGB_2_black_and_white
	.type	convert_RGB_2_black_and_white, @function
convert_RGB_2_black_and_white:
.LFB39:
	.cfi_startproc
	leaq	3(%rdi), %rcx
	addq	$307203, %rdi
	.p2align 4,,10
	.p2align 3
.L3:
	movzbl	(%rcx), %eax
	addq	$4, %rcx
	addq	$4, %rsi
	imull	$1224, %eax, %edx
	movzbl	307196(%rcx), %eax
	imull	$2404, %eax, %eax
	addl	%edx, %eax
	movzbl	614396(%rcx), %edx
	movb	$0, -3(%rsi)
	movb	$0, -2(%rsi)
	movb	$0, -1(%rsi)
	imull	$467, %edx, %edx
	addl	%edx, %eax
	shrl	$12, %eax
	movb	%al, -4(%rsi)
	cmpq	%rcx, %rdi
	jne	.L3
	rep ret
	.cfi_endproc
.LFE39:
	.size	convert_RGB_2_black_and_white, .-convert_RGB_2_black_and_white
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"CPU cycles: %ld\n"
	.section	.text.unlikely
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
#APP
# 9 "example1.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	movq	%rdx, %r9
	movl	%eax, %r10d
	movl	$10000, %r8d
	salq	$32, %r9
	.p2align 4,,10
	.p2align 3
.L7:
	movl	$output_IMG, %esi
	movl	$opt_input_IMG, %edi
	call	convert_RGB_2_black_and_white
	subl	$1, %r8d
	jne	.L7
#APP
# 9 "example1.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	addq	%r10, %r9
	movl	%eax, %eax
	salq	$32, %rdx
	subq	%r9, %rax
	movl	$.LC2, %esi
	movl	$1, %edi
	addq	%rax, %rdx
	xorl	%eax, %eax
	call	__printf_chk
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
	.comm	opt_input_IMG,921600,32
	.comm	output_IMG,307200,32
	.comm	input_IMG,921600,32
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits

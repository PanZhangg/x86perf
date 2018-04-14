	.file	"example1.c"
	.text
	.globl	trace_cpu_time_now
	.type	trace_cpu_time_now, @function
trace_cpu_time_now:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 9 "example1.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	movl	%eax, -8(%rbp)
	movl	%edx, -4(%rbp)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	salq	$32, %rdx
	addq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	trace_cpu_time_now, .-trace_cpu_time_now
	.comm	input_IMG,921600,32
	.comm	output_IMG,307200,32
	.comm	opt_input_IMG,921600,32
	.globl	convert_RGB_2_black_and_white
	.type	convert_RGB_2_black_and_white, @function
convert_RGB_2_black_and_white:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movl	$0, -64(%rbp)
	movl	$0, -60(%rbp)
	movl	$0, -56(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -44(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L4
.L5:
	movq	-88(%rbp), %rdx
	movl	-68(%rbp), %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$1224, %eax, %eax
	movl	%eax, -48(%rbp)
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$1224, %eax, %eax
	movl	%eax, -48(%rbp)
	movl	-68(%rbp), %eax
	addl	$2, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$1224, %eax, %eax
	movl	%eax, -48(%rbp)
	movl	-68(%rbp), %eax
	addl	$3, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$1224, %eax, %eax
	movl	%eax, -48(%rbp)
	movq	-88(%rbp), %rdx
	movl	-68(%rbp), %eax
	cltq
	movzbl	307200(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$2404, %eax, %eax
	movl	%eax, -32(%rbp)
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	307200(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$2404, %eax, %eax
	movl	%eax, -32(%rbp)
	movl	-68(%rbp), %eax
	addl	$2, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	307200(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$2404, %eax, %eax
	movl	%eax, -32(%rbp)
	movl	-68(%rbp), %eax
	addl	$3, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	307200(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$2404, %eax, %eax
	movl	%eax, -32(%rbp)
	movq	-88(%rbp), %rdx
	movl	-68(%rbp), %eax
	cltq
	movzbl	614400(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$467, %eax, %eax
	movl	%eax, -16(%rbp)
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	614400(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$467, %eax, %eax
	movl	%eax, -16(%rbp)
	movl	-68(%rbp), %eax
	addl	$2, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	614400(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$467, %eax, %eax
	movl	%eax, -16(%rbp)
	movl	-68(%rbp), %eax
	addl	$3, %eax
	movq	-88(%rbp), %rdx
	cltq
	movzbl	614400(%rdx,%rax), %eax
	movzbl	%al, %eax
	imull	$467, %eax, %eax
	movl	%eax, -16(%rbp)
	movl	-48(%rbp), %edx
	movl	-32(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -64(%rbp)
	movl	-44(%rbp), %edx
	movl	-28(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -60(%rbp)
	movl	-40(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -56(%rbp)
	movl	-36(%rbp), %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -52(%rbp)
	movl	-68(%rbp), %eax
	movslq	%eax, %rdx
	movq	-96(%rbp), %rax
	addq	%rdx, %rax
	movl	-64(%rbp), %edx
	shrl	$12, %edx
	movb	%dl, (%rax)
	movl	-68(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	-96(%rbp), %rax
	addq	%rdx, %rax
	movl	-60(%rbp), %edx
	shrl	$12, %edx
	movb	%dl, (%rax)
	movl	-68(%rbp), %eax
	cltq
	leaq	2(%rax), %rdx
	movq	-96(%rbp), %rax
	addq	%rdx, %rax
	movl	-56(%rbp), %edx
	shrl	$12, %edx
	movb	%dl, (%rax)
	movl	-68(%rbp), %eax
	cltq
	leaq	3(%rax), %rdx
	movq	-96(%rbp), %rax
	addq	%rdx, %rax
	movl	-52(%rbp), %edx
	shrl	$12, %edx
	movb	%dl, (%rax)
	addl	$4, -68(%rbp)
.L4:
	cmpl	$307199, -68(%rbp)
	jle	.L5
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	convert_RGB_2_black_and_white, .-convert_RGB_2_black_and_white
	.section	.rodata
.LC0:
	.string	"CPU cycles: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -20(%rbp)
	call	trace_cpu_time_now
	movq	%rax, -16(%rbp)
	jmp	.L7
.L8:
	movl	$output_IMG, %esi
	movl	$opt_input_IMG, %edi
	call	convert_RGB_2_black_and_white
	addl	$1, -20(%rbp)
.L7:
	cmpl	$9999, -20(%rbp)
	jbe	.L8
	call	trace_cpu_time_now
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	subq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits

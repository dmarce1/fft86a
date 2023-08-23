	.file	"fft.cpp"
	.text
	.section	.text._ZNSt6vectorIdSaIdEED2Ev,"axG",@progbits,_ZNSt6vectorIdSaIdEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIdSaIdEED2Ev
	.type	_ZNSt6vectorIdSaIdEED2Ev, @function
_ZNSt6vectorIdSaIdEED2Ev:
.LFB10034:
	.cfi_startproc
	movq	(%rdi), %rax
	testq	%rax, %rax
	je	.L3
	movq	16(%rdi), %rsi
	movq	%rax, %rdi
	subq	%rax, %rsi
	jmp	_ZdlPvm
	.p2align 4
	.p2align 3
.L3:
	ret
	.cfi_endproc
.LFE10034:
	.size	_ZNSt6vectorIdSaIdEED2Ev, .-_ZNSt6vectorIdSaIdEED2Ev
	.weak	_ZNSt6vectorIdSaIdEED1Ev
	.set	_ZNSt6vectorIdSaIdEED1Ev,_ZNSt6vectorIdSaIdEED2Ev
	.text
	.p2align 4
	.globl	_Z14fft_1d_batch_3PSt7complexIdEii
	.type	_Z14fft_1d_batch_3PSt7complexIdEii, @function
_Z14fft_1d_batch_3PSt7complexIdEii:
.LFB9673:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE9673:
	.size	_Z14fft_1d_batch_3PSt7complexIdEii, .-_Z14fft_1d_batch_3PSt7complexIdEii
	.section	.text._Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,"axG",@progbits,_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,comdat
	.p2align 4
	.weak	_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii
	.type	_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii, @function
_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii:
.LFB10052:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA10052
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %r12
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movl	%ecx, %ebp
	movl	%edx, %ebx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%rsp, %rdi
.LEHB0:
	call	_ZN6digitsC1ERKSt6vectorIiSaIiEE
.LEHE0:
	xorl	%esi, %esi
	movq	%rsp, %rdi
.LEHB1:
	call	_ZN6digitsaSEi
	jmp	.L8
	.p2align 4
	.p2align 3
.L36:
	cmpl	%eax, %r13d
	jl	.L35
.L8:
	movq	%rsp, %rdi
	call	_ZN6digitsppEv
	movq	%rsp, %rdi
	call	_ZNK6digits6to_intEv
	movq	%rsp, %rdi
	movl	%eax, %r13d
	call	_ZNK6digits14to_int_reverseEv
.LEHE1:
	cmpl	%ebx, %r13d
	jl	.L36
	movq	24(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L12
	movq	40(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm
.L12:
	movq	(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L33
	movq	16(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm
.L33:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L35:
	.cfi_restore_state
	imull	%ebp, %r13d
	imull	%ebp, %eax
	testl	%ebp, %ebp
	jle	.L8
	movslq	%r13d, %r13
	movslq	%ebp, %rsi
	cltq
	movq	%r13, %rdi
	addq	%r13, %rsi
	salq	$4, %rax
	salq	$4, %rdi
	salq	$4, %rsi
	leaq	(%r12,%rdi), %rdx
	addq	%r12, %rsi
	.p2align 4
	.p2align 3
.L10:
	movq	%rdx, %rcx
	vmovsd	(%rdx), %xmm1
	vmovsd	8(%rdx), %xmm0
	addq	$16, %rdx
	subq	%rdi, %rcx
	vmovsd	(%rcx,%rax), %xmm2
	vmovsd	%xmm2, -16(%rdx)
	vmovsd	8(%rcx,%rax), %xmm2
	vmovsd	%xmm2, -8(%rdx)
	vmovsd	%xmm1, (%rcx,%rax)
	vmovsd	%xmm0, 8(%rcx,%rax)
	cmpq	%rdx, %rsi
	jne	.L10
	jmp	.L8
.L17:
	movq	%rax, %rbx
.L14:
	movq	24(%rsp), %rdi
	movq	40(%rsp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L32
	vzeroupper
	call	_ZdlPvm
.L15:
	movq	(%rsp), %rdi
	movq	16(%rsp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L16
	call	_ZdlPvm
.L16:
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L32:
	vzeroupper
	jmp	.L15
	.cfi_endproc
.LFE10052:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,"aG",@progbits,_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,comdat
.LLSDA10052:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE10052-.LLSDACSB10052
.LLSDACSB10052:
	.uleb128 .LEHB0-.LFB10052
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB10052
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L17-.LFB10052
	.uleb128 0
	.uleb128 .LEHB2-.LFB10052
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE10052:
	.section	.text._Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,"axG",@progbits,_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii,comdat
	.size	_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii, .-_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii
	.section	.rodata._ZNSt6vectorIdSaIdEE17_M_default_appendEm.str1.1,"aMS",@progbits,1
.LC1:
	.string	"vector::_M_default_append"
	.section	.text._ZNSt6vectorIdSaIdEE17_M_default_appendEm,"axG",@progbits,_ZNSt6vectorIdSaIdEE17_M_default_appendEm,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	.type	_ZNSt6vectorIdSaIdEE17_M_default_appendEm, @function
_ZNSt6vectorIdSaIdEE17_M_default_appendEm:
.LFB10242:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L63
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movabsq	$1152921504606846975, %rax
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	movq	%rdi, %r12
	movq	%rdx, %r15
	subq	(%rdi), %r15
	movq	%r15, %rcx
	sarq	$3, %rcx
	subq	%rcx, %rax
	movq	%rax, %rsi
	movq	16(%rdi), %rax
	subq	%rdx, %rax
	sarq	$3, %rax
	cmpq	%rbx, %rax
	jnb	.L66
	cmpq	%rbx, %rsi
	jb	.L67
	leaq	(%rbx,%rcx), %r14
	cmpq	%rbx, %rcx
	jb	.L68
	leaq	(%rcx,%rcx), %rax
	movabsq	$9223372036854775800, %r13
	cmpq	%rcx, %rax
	jnb	.L69
.L43:
	movq	%r13, %rdi
	call	_Znwm
	movq	(%r12), %r8
	movq	8(%r12), %rcx
	addq	%rax, %r13
	movq	%rax, %rbp
	leaq	(%rax,%r15), %rax
	movq	$0x000000000, (%rax)
	subq	%r8, %rcx
	decq	%rbx
	je	.L47
	leaq	8(%rax), %rdi
	leaq	0(,%rbx,8), %rdx
	xorl	%esi, %esi
	movq	%rcx, 8(%rsp)
	movq	%r8, (%rsp)
	call	memset
	movq	(%rsp), %r8
	movq	8(%rsp), %rcx
.L47:
	testq	%rcx, %rcx
	jg	.L70
	testq	%r8, %r8
	jne	.L71
.L49:
	leaq	0(%rbp,%r14,8), %rax
	vmovq	%rbp, %xmm1
	movq	%r13, 16(%r12)
	vpinsrq	$1, %rax, %xmm1, %xmm0
	vmovdqu	%xmm0, (%r12)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L66:
	.cfi_restore_state
	decq	%rbx
	movq	$0x000000000, (%rdx)
	leaq	8(%rdx), %rcx
	je	.L40
	leaq	(%rcx,%rbx,8), %rax
	movq	%rcx, %rdi
	xorl	%esi, %esi
	subq	%rdx, %rax
	leaq	-8(%rax), %rbx
	movq	%rbx, %rdx
	call	memset
	movq	%rax, %rcx
	addq	%rbx, %rcx
.L40:
	movq	%rcx, 8(%r12)
	addq	$24, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L63:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
	.p2align 4
	.p2align 3
.L68:
	.cfi_def_cfa_offset 80
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movabsq	$1152921504606846975, %r13
	cmpq	%r13, %r14
	cmovbe	%r14, %r13
	salq	$3, %r13
	jmp	.L43
	.p2align 4
	.p2align 3
.L70:
	movq	%r8, %rsi
	movq	%rcx, %rdx
	movq	%rbp, %rdi
	movq	%r8, (%rsp)
	call	memmove
	movq	16(%r12), %rsi
	movq	(%rsp), %r8
	subq	%r8, %rsi
.L48:
	movq	%r8, %rdi
	call	_ZdlPvm
	jmp	.L49
	.p2align 4
	.p2align 3
.L71:
	movq	16(%r12), %rsi
	subq	%r8, %rsi
	jmp	.L48
.L67:
	movl	$.LC1, %edi
	call	_ZSt20__throw_length_errorPKc
.L69:
	movabsq	$1152921504606846975, %rdx
	cmpq	%rdx, %rax
	cmova	%rdx, %rax
	leaq	0(,%rax,8), %r13
	jmp	.L43
	.cfi_endproc
.LFE10242:
	.size	_ZNSt6vectorIdSaIdEE17_M_default_appendEm, .-_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	.text
	.p2align 4
	.globl	_Z13inv_perf_shufPdi
	.type	_Z13inv_perf_shufPdi, @function
_Z13inv_perf_shufPdi:
.LFB9658:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movl	%esi, %r12d
	movq	%rdi, %rbx
	andq	$-32, %rsp
	subq	$32, %rsp
	cmpb	$0, %fs:_ZGVZ13inv_perf_shufPdiE3tmp@tpoff
	je	.L93
.L73:
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff+8, %rdx
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff, %rdi
	movslq	%r12d, %rax
	leal	(%r12,%r12), %esi
	leaq	(%rbx,%rax,8), %r13
	movslq	%esi, %rsi
	leaq	0(,%rsi,8), %r14
	movq	%rdx, %rax
	subq	%rdi, %rax
	sarq	$3, %rax
	cmpq	%rsi, %rax
	jb	.L94
	cmpq	%rax, %rsi
	jb	.L95
.L75:
	movq	%rbx, %rsi
	movq	%r14, %rdx
	call	memcpy
	testl	%r12d, %r12d
	leal	3(%r12), %esi
	movl	%r12d, %edi
	cmovns	%r12d, %esi
	shrl	$31, %edi
	addl	%r12d, %edi
	movl	%esi, %r8d
	movl	%edi, %r9d
	sarl	$2, %r8d
	andl	$-2, %edi
	sarl	%r9d
	andl	$-4, %esi
	jle	.L82
	leal	-1(%rsi), %ecx
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff, %rdx
	xorl	%eax, %eax
	shrl	$2, %ecx
	incl	%ecx
	salq	$5, %rcx
	.p2align 4
	.p2align 3
.L81:
	vpermpd	$216, (%rdx,%rax,2), %ymm0
	vpermpd	$216, 32(%rdx,%rax,2), %ymm1
	vinsertf128	$1, %xmm1, %ymm0, %ymm2
	vperm2f128	$49, %ymm1, %ymm0, %ymm0
	vmovupd	%ymm2, (%rbx,%rax)
	vmovupd	%ymm0, 0(%r13,%rax)
	addq	$32, %rax
	cmpq	%rcx, %rax
	jne	.L81
	vzeroupper
.L82:
	cmpl	%edi, %esi
	jge	.L80
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff, %rax
	sall	$3, %r8d
	movslq	%r8d, %r8
	vmovupd	(%rax,%r8,8), %xmm0
	vmovupd	16(%rax,%r8,8), %xmm1
	movslq	%esi, %rax
	salq	$3, %rax
	vmovapd	%xmm0, (%rsp)
	vmovapd	%xmm1, 16(%rsp)
	vmovlpd	%xmm1, 8(%rsp)
	vmovapd	(%rsp), %xmm3
	vmovhpd	%xmm0, 16(%rsp)
	vmovapd	16(%rsp), %xmm4
	vmovupd	%xmm3, (%rbx,%rax)
	vmovupd	%xmm4, 0(%r13,%rax)
.L80:
	cmpl	%esi, %r12d
	jle	.L91
	cmpl	%edi, %r12d
	jne	.L96
.L91:
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L95:
	.cfi_restore_state
	leaq	(%rdi,%r14), %rax
	cmpq	%rax, %rdx
	je	.L75
	movq	%rax, %fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff+8
	jmp	.L75
	.p2align 4
	.p2align 3
.L96:
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff, %rax
	sall	$2, %r9d
	movslq	%edi, %rdi
	movslq	%r9d, %rdx
	incl	%r9d
	salq	$3, %rdi
	movslq	%r9d, %r9
	vmovsd	(%rax,%rdx,8), %xmm0
	vmovsd	%xmm0, (%rbx,%rdi)
	vmovsd	(%rax,%r9,8), %xmm0
	vmovsd	%xmm0, 0(%r13,%rdi)
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L94:
	.cfi_restore_state
	subq	%rax, %rsi
	movq	%fs:0, %rax
	leaq	_ZZ13inv_perf_shufPdiE3tmp@tpoff(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	movq	%fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff, %rdi
	jmp	.L75
	.p2align 4
	.p2align 3
.L93:
	movq	%fs:0, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$__dso_handle, %edx
	movl	$_ZNSt6vectorIdSaIdEED1Ev, %edi
	vmovdqa	%xmm0, %fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff
	movq	$0, %fs:_ZZ13inv_perf_shufPdiE3tmp@tpoff+16
	movb	$1, %fs:_ZGVZ13inv_perf_shufPdiE3tmp@tpoff
	leaq	_ZZ13inv_perf_shufPdiE3tmp@tpoff(%rax), %rsi
	call	__cxa_thread_atexit
	jmp	.L73
	.cfi_endproc
.LFE9658:
	.size	_Z13inv_perf_shufPdi, .-_Z13inv_perf_shufPdi
	.p2align 4
	.globl	_Z13inv_perf_shufPSt7complexIdEii
	.type	_Z13inv_perf_shufPSt7complexIdEii, @function
_Z13inv_perf_shufPSt7complexIdEii:
.LFB9671:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L103
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	leal	(%rdx,%rdx), %r12d
	movslq	%r12d, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movl	%esi, %r13d
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	%edx, %r14d
	salq	$3, %r12
	movq	%rdi, %rbx
	xorl	%ebp, %ebp
	.p2align 4
	.p2align 3
.L99:
	movq	%rbx, %rdi
	movl	%r14d, %esi
	incl	%ebp
	addq	%r12, %rbx
	call	_Z13inv_perf_shufPdi
	cmpl	%ebp, %r13d
	jne	.L99
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L103:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	ret
	.cfi_endproc
.LFE9671:
	.size	_Z13inv_perf_shufPSt7complexIdEii, .-_Z13inv_perf_shufPSt7complexIdEii
	.p2align 4
	.globl	_Z9perf_shufPdi
	.type	_Z9perf_shufPdi, @function
_Z9perf_shufPdi:
.LFB9669:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%esi, %r12d
	movq	%rdi, %rbx
	andq	$-32, %rsp
	subq	$32, %rsp
	cmpb	$0, %fs:_ZGVZ9perf_shufPdiE4tmpx@tpoff
	je	.L126
	cmpb	$0, %fs:_ZGVZ9perf_shufPdiE4tmpy@tpoff
	je	.L127
.L108:
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff+8, %rcx
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff, %rdx
	movslq	%r12d, %r13
	leaq	0(,%r13,8), %r15
	leaq	(%rbx,%r15), %r14
	movq	%rcx, %rax
	subq	%rdx, %rax
	sarq	$3, %rax
	cmpq	%r13, %rax
	jb	.L128
	cmpq	%rax, %r13
	jnb	.L110
	addq	%r15, %rdx
	cmpq	%rdx, %rcx
	je	.L110
	movq	%rdx, %fs:_ZZ9perf_shufPdiE4tmpx@tpoff+8
.L110:
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff+8, %rcx
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff, %rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	sarq	$3, %rax
	cmpq	%r13, %rax
	jb	.L129
	cmpq	%rax, %r13
	jb	.L130
.L112:
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff, %rdi
	movq	%r15, %rdx
	movq	%rbx, %rsi
	call	memcpy
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff, %rdi
	movq	%r14, %rsi
	movq	%r15, %rdx
	call	memcpy
	testl	%r12d, %r12d
	leal	3(%r12), %ecx
	movl	%r12d, %esi
	cmovns	%r12d, %ecx
	shrl	$31, %esi
	addl	%r12d, %esi
	movl	%ecx, %r9d
	movl	%esi, %r10d
	sarl	$2, %r9d
	andl	$-2, %esi
	sarl	%r10d
	andl	$-4, %ecx
	jle	.L113
	leal	-1(%rcx), %edx
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff, %r8
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff, %rdi
	xorl	%eax, %eax
	shrl	$2, %edx
	incl	%edx
	salq	$5, %rdx
	.p2align 4
	.p2align 3
.L114:
	vmovupd	(%r8,%rax), %ymm2
	vinsertf128	$1, (%rdi,%rax), %ymm2, %ymm1
	vperm2f128	$49, (%rdi,%rax), %ymm2, %ymm0
	vpermpd	$216, %ymm1, %ymm1
	vpermpd	$216, %ymm0, %ymm0
	vmovupd	%ymm1, (%rbx,%rax,2)
	vmovupd	%ymm0, 32(%rbx,%rax,2)
	addq	$32, %rax
	cmpq	%rdx, %rax
	jne	.L114
	vzeroupper
.L113:
	cmpl	%esi, %ecx
	jge	.L115
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff, %rdx
	movslq	%ecx, %rax
	sall	$3, %r9d
	salq	$3, %rax
	movslq	%r9d, %r9
	vmovupd	(%rdx,%rax), %xmm0
	vmovapd	%xmm0, (%rsp)
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff, %rdx
	vmovupd	(%rdx,%rax), %xmm1
	vmovapd	%xmm1, 16(%rsp)
	vmovlpd	%xmm1, 8(%rsp)
	vmovhpd	%xmm0, 16(%rsp)
	vmovapd	(%rsp), %xmm4
	vmovapd	16(%rsp), %xmm5
	vmovupd	%xmm4, (%rbx,%r9,8)
	vmovupd	%xmm5, 16(%rbx,%r9,8)
.L115:
	cmpl	%ecx, %r12d
	jle	.L124
	cmpl	%esi, %r12d
	jne	.L131
.L124:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L130:
	.cfi_restore_state
	addq	%r15, %rdx
	cmpq	%rdx, %rcx
	je	.L112
	movq	%rdx, %fs:_ZZ9perf_shufPdiE4tmpy@tpoff+8
	jmp	.L112
	.p2align 4
	.p2align 3
.L131:
	movq	%fs:_ZZ9perf_shufPdiE4tmpx@tpoff, %rax
	movslq	%esi, %rsi
	sall	$2, %r10d
	salq	$3, %rsi
	movslq	%r10d, %r10
	vmovsd	(%rax,%rsi), %xmm0
	vmovsd	%xmm0, (%rbx,%r10,8)
	movq	%fs:_ZZ9perf_shufPdiE4tmpy@tpoff, %rax
	vmovsd	(%rax,%rsi), %xmm0
	vmovsd	%xmm0, 8(%rbx,%r10,8)
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L129:
	.cfi_restore_state
	movq	%r13, %rsi
	subq	%rax, %rsi
	movq	%fs:0, %rax
	leaq	_ZZ9perf_shufPdiE4tmpy@tpoff(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	jmp	.L112
	.p2align 4
	.p2align 3
.L126:
	movq	%fs:0, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, %fs:_ZZ9perf_shufPdiE4tmpx@tpoff+16
	movb	$1, %fs:_ZGVZ9perf_shufPdiE4tmpx@tpoff
	vmovdqa	%xmm0, %fs:_ZZ9perf_shufPdiE4tmpx@tpoff
	movl	$__dso_handle, %edx
	movl	$_ZNSt6vectorIdSaIdEED1Ev, %edi
	leaq	_ZZ9perf_shufPdiE4tmpx@tpoff(%rax), %rsi
	call	__cxa_thread_atexit
	cmpb	$0, %fs:_ZGVZ9perf_shufPdiE4tmpy@tpoff
	jne	.L108
.L127:
	movq	%fs:0, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$__dso_handle, %edx
	movl	$_ZNSt6vectorIdSaIdEED1Ev, %edi
	vmovdqa	%xmm0, %fs:_ZZ9perf_shufPdiE4tmpy@tpoff
	movq	$0, %fs:_ZZ9perf_shufPdiE4tmpy@tpoff+16
	movb	$1, %fs:_ZGVZ9perf_shufPdiE4tmpy@tpoff
	leaq	_ZZ9perf_shufPdiE4tmpy@tpoff(%rax), %rsi
	call	__cxa_thread_atexit
	jmp	.L108
	.p2align 4
	.p2align 3
.L128:
	movq	%r13, %rsi
	subq	%rax, %rsi
	movq	%fs:0, %rax
	leaq	_ZZ9perf_shufPdiE4tmpx@tpoff(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	jmp	.L110
	.cfi_endproc
.LFE9669:
	.size	_Z9perf_shufPdi, .-_Z9perf_shufPdi
	.p2align 4
	.globl	_Z9perf_shufPSt7complexIdEii
	.type	_Z9perf_shufPSt7complexIdEii, @function
_Z9perf_shufPSt7complexIdEii:
.LFB9672:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L138
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	leal	(%rdx,%rdx), %r12d
	movslq	%r12d, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movl	%esi, %r13d
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	%edx, %r14d
	salq	$3, %r12
	movq	%rdi, %rbx
	xorl	%ebp, %ebp
	.p2align 4
	.p2align 3
.L134:
	movq	%rbx, %rdi
	movl	%r14d, %esi
	incl	%ebp
	addq	%r12, %rbx
	call	_Z9perf_shufPdi
	cmpl	%ebp, %r13d
	jne	.L134
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L138:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	ret
	.cfi_endproc
.LFE9672:
	.size	_Z9perf_shufPSt7complexIdEii, .-_Z9perf_shufPSt7complexIdEii
	.section	.text._Z9butterflyI4v4dfLi3EEvPdS1_i,"axG",@progbits,_Z9butterflyI4v4dfLi3EEvPdS1_i,comdat
	.p2align 4
	.weak	_Z9butterflyI4v4dfLi3EEvPdS1_i
	.type	_Z9butterflyI4v4dfLi3EEvPdS1_i, @function
_Z9butterflyI4v4dfLi3EEvPdS1_i:
.LFB10268:
	.cfi_startproc
	movslq	%edx, %rdx
	vbroadcastsd	.LC3(%rip), %ymm4
	vbroadcastsd	.LC5(%rip), %ymm5
	salq	$3, %rdx
	leaq	(%rdi,%rdx), %rcx
	leaq	(%rsi,%rdx), %rax
	leaq	(%rcx,%rdx), %r8
	addq	%rax, %rdx
	vmovupd	(%r8), %ymm6
	vmovupd	(%rdx), %ymm7
	vaddpd	(%rcx), %ymm6, %ymm2
	vsubpd	(%rax), %ymm7, %ymm3
	vaddpd	(%rax), %ymm7, %ymm0
	vsubpd	(%rcx), %ymm6, %ymm1
	vaddpd	(%rdi), %ymm2, %ymm7
	vfmadd213pd	(%rdi), %ymm4, %ymm2
	vaddpd	(%rsi), %ymm0, %ymm6
	vfmadd213pd	(%rsi), %ymm4, %ymm0
	vxorpd	%xmm4, %xmm4, %xmm4
	vfmadd132pd	%ymm5, %ymm4, %ymm3
	vfmadd132pd	%ymm5, %ymm4, %ymm1
	vmovupd	%ymm7, (%rdi)
	vmovupd	%ymm6, (%rsi)
	vsubpd	%ymm3, %ymm2, %ymm4
	vaddpd	%ymm3, %ymm2, %ymm2
	vmovupd	%ymm4, (%rcx)
	vaddpd	%ymm1, %ymm0, %ymm4
	vsubpd	%ymm1, %ymm0, %ymm0
	vmovupd	%ymm4, (%rax)
	vmovupd	%ymm2, (%r8)
	vmovupd	%ymm0, (%rdx)
	vzeroupper
	ret
	.cfi_endproc
.LFE10268:
	.size	_Z9butterflyI4v4dfLi3EEvPdS1_i, .-_Z9butterflyI4v4dfLi3EEvPdS1_i
	.section	.text._Z9butterflyI4v2dfLi3EEvPdS1_i,"axG",@progbits,_Z9butterflyI4v2dfLi3EEvPdS1_i,comdat
	.p2align 4
	.weak	_Z9butterflyI4v2dfLi3EEvPdS1_i
	.type	_Z9butterflyI4v2dfLi3EEvPdS1_i, @function
_Z9butterflyI4v2dfLi3EEvPdS1_i:
.LFB10280:
	.cfi_startproc
	movslq	%edx, %rdx
	vmovddup	.LC3(%rip), %xmm4
	vmovddup	.LC5(%rip), %xmm5
	salq	$3, %rdx
	leaq	(%rdi,%rdx), %rcx
	leaq	(%rsi,%rdx), %rax
	leaq	(%rcx,%rdx), %r8
	addq	%rax, %rdx
	vmovupd	(%r8), %xmm6
	vmovupd	(%rdx), %xmm7
	vaddpd	(%rcx), %xmm6, %xmm2
	vsubpd	(%rax), %xmm7, %xmm3
	vaddpd	(%rax), %xmm7, %xmm0
	vsubpd	(%rcx), %xmm6, %xmm1
	vaddpd	(%rdi), %xmm2, %xmm7
	vfmadd213pd	(%rdi), %xmm4, %xmm2
	vaddpd	(%rsi), %xmm0, %xmm6
	vfmadd213pd	(%rsi), %xmm4, %xmm0
	vxorpd	%xmm4, %xmm4, %xmm4
	vfmadd132pd	%xmm5, %xmm4, %xmm3
	vfmadd132pd	%xmm5, %xmm4, %xmm1
	vmovupd	%xmm7, (%rdi)
	vmovupd	%xmm6, (%rsi)
	vsubpd	%xmm3, %xmm2, %xmm4
	vaddpd	%xmm3, %xmm2, %xmm2
	vmovupd	%xmm4, (%rcx)
	vaddpd	%xmm1, %xmm0, %xmm4
	vsubpd	%xmm1, %xmm0, %xmm0
	vmovupd	%xmm4, (%rax)
	vmovupd	%xmm2, (%r8)
	vmovupd	%xmm0, (%rdx)
	ret
	.cfi_endproc
.LFE10280:
	.size	_Z9butterflyI4v2dfLi3EEvPdS1_i, .-_Z9butterflyI4v2dfLi3EEvPdS1_i
	.section	.text._Z9butterflyILi3EEvPdS0_i,"axG",@progbits,_Z9butterflyILi3EEvPdS0_i,comdat
	.p2align 4
	.weak	_Z9butterflyILi3EEvPdS0_i
	.type	_Z9butterflyILi3EEvPdS0_i, @function
_Z9butterflyILi3EEvPdS0_i:
.LFB10286:
	.cfi_startproc
	movq	%rdi, %rcx
	movq	%rsi, %rax
	cmpl	$1, %edx
	jne	.L150
	vmovdqu	(%rdi), %xmm7
	movq	16(%rdi), %rsi
	movq	%rsi, -56(%rsp)
	movq	16(%rax), %rsi
	vmovdqa	%xmm7, -72(%rsp)
	vmovdqu	(%rax), %xmm7
	movq	%rsi, -24(%rsp)
	vmovdqa	%xmm7, -40(%rsp)
.L145:
	vmovsd	-64(%rsp), %xmm5
	vmovsd	-32(%rsp), %xmm4
	vmovsd	-56(%rsp), %xmm1
	vmovsd	-24(%rsp), %xmm0
	vmovddup	-72(%rsp), %xmm6
	vaddsd	%xmm1, %xmm5, %xmm3
	vsubsd	%xmm5, %xmm1, %xmm1
	vmovddup	-40(%rsp), %xmm5
	vaddsd	%xmm0, %xmm4, %xmm2
	vsubsd	%xmm4, %xmm0, %xmm0
	vmovapd	.LC8(%rip), %xmm4
	vmovddup	%xmm3, %xmm3
	vmovddup	%xmm1, %xmm1
	vmovddup	%xmm2, %xmm2
	vmovddup	%xmm0, %xmm0
	vfmadd132pd	%xmm4, %xmm5, %xmm2
	vmovapd	.LC9(%rip), %xmm5
	vfmadd132pd	%xmm4, %xmm6, %xmm3
	vxorpd	%xmm4, %xmm4, %xmm4
	vmovsd	%xmm3, %xmm3, %xmm8
	vmovsd	%xmm2, %xmm2, %xmm7
	vfmadd132pd	%xmm5, %xmm4, %xmm0
	vfmadd132pd	%xmm5, %xmm4, %xmm1
	vunpckhpd	%xmm3, %xmm3, %xmm4
	vunpckhpd	%xmm0, %xmm0, %xmm0
	vunpckhpd	%xmm1, %xmm1, %xmm1
	vsubsd	%xmm0, %xmm4, %xmm6
	vaddsd	%xmm4, %xmm0, %xmm0
	vunpcklpd	%xmm6, %xmm3, %xmm5
	vunpckhpd	%xmm2, %xmm2, %xmm3
	vmovsd	%xmm0, -56(%rsp)
	vmovapd	%xmm5, -72(%rsp)
	vaddsd	%xmm1, %xmm3, %xmm5
	vsubsd	%xmm1, %xmm3, %xmm3
	vunpcklpd	%xmm5, %xmm2, %xmm2
	vmovsd	%xmm3, -24(%rsp)
	vmovapd	%xmm2, -40(%rsp)
	cmpl	$1, %edx
	jne	.L151
	leaq	23(%rcx), %rdx
	subq	%rax, %rdx
	cmpq	$46, %rdx
	jbe	.L148
	vmovdqa	-72(%rsp), %xmm7
	movq	-56(%rsp), %rdx
	movq	%rdx, 16(%rcx)
	movq	-24(%rsp), %rdx
	vmovdqu	%xmm7, (%rcx)
	vmovdqa	-40(%rsp), %xmm7
	movq	%rdx, 16(%rax)
	vmovdqu	%xmm7, (%rax)
	ret
	.p2align 4
	.p2align 3
.L150:
	vmovsd	(%rcx), %xmm0
	movslq	%edx, %rsi
	leaq	0(,%rsi,8), %rdi
	vmovhpd	(%rcx,%rsi,8), %xmm0, %xmm0
	vmovapd	%xmm0, -72(%rsp)
	vmovsd	(%rax), %xmm0
	vmovhpd	(%rax,%rsi,8), %xmm0, %xmm0
	vmovapd	%xmm0, -40(%rsp)
	vmovsd	(%rcx,%rdi,2), %xmm0
	vmovsd	%xmm0, -56(%rsp)
	vmovsd	(%rax,%rdi,2), %xmm0
	vmovsd	%xmm0, -24(%rsp)
	jmp	.L145
	.p2align 4
	.p2align 3
.L151:
	movslq	%edx, %rdx
	vmovsd	%xmm8, (%rcx)
	vmovsd	%xmm7, (%rax)
	salq	$3, %rdx
	addq	%rdx, %rcx
	addq	%rdx, %rax
	vmovsd	%xmm6, (%rcx)
	vmovsd	%xmm5, (%rax)
	vmovsd	%xmm0, (%rcx,%rdx)
	vmovsd	%xmm3, (%rax,%rdx)
	ret
	.p2align 4
	.p2align 3
.L148:
	vmovsd	%xmm8, (%rcx)
	vmovsd	%xmm7, (%rax)
	vmovsd	%xmm6, 8(%rcx)
	vmovsd	%xmm5, 8(%rax)
	vmovsd	%xmm0, 16(%rcx)
	vmovsd	%xmm3, 16(%rax)
	ret
	.cfi_endproc
.LFE10286:
	.size	_Z9butterflyILi3EEvPdS0_i, .-_Z9butterflyILi3EEvPdS0_i
	.section	.text._Z12fft_1d_batchILi3EEvPdii,"axG",@progbits,_Z12fft_1d_batchILi3EEvPdii,comdat
	.p2align 4
	.weak	_Z12fft_1d_batchILi3EEvPdii
	.type	_Z12fft_1d_batchILi3EEvPdii, @function
_Z12fft_1d_batchILi3EEvPdii:
.LFB10057:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	addq	$-128, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, 72(%rsp)
	movl	%esi, 20(%rsp)
	movl	%edx, 16(%rsp)
	cmpb	$0, %fs:_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff
	je	.L181
	cmpb	$0, %fs:_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff
	je	.L182
.L154:
	movq	%fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff+8, %rcx
	movq	%fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff, %rax
	movq	%rcx, %rdx
	subq	%rax, %rdx
	cmpq	$16, %rdx
	jbe	.L183
	cmpq	$24, %rdx
	jbe	.L156
	addq	$24, %rax
	cmpq	%rax, %rcx
	je	.L156
	movq	%rax, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff+8
.L156:
	movq	%fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff+8, %rcx
	movq	%fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff, %rax
	movq	%rcx, %rdx
	subq	%rax, %rdx
	cmpq	$16, %rdx
	jbe	.L184
	cmpq	$24, %rdx
	ja	.L185
.L158:
	movslq	20(%rsp), %rax
	movq	%rax, %rcx
	imulq	$1431655766, %rax, %rax
	movl	%ecx, %edx
	sarl	$31, %edx
	shrq	$32, %rax
	movl	%eax, %esi
	subl	%edx, %esi
	cmpl	$1, %ecx
	jle	.L179
	movl	16(%rsp), %edi
	movl	$1, 24(%rsp)
	movl	%esi, %r10d
	movl	%edi, %ecx
	sarl	$31, %ecx
	movl	%ecx, %edx
	movl	%edi, %ecx
	shrl	$30, %edx
	leal	(%rdi,%rdx), %eax
	andl	$3, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%edi, %eax
	shrl	$31, %eax
	movl	%ecx, 120(%rsp)
	addl	%edi, %eax
	andl	$-2, %eax
	movl	%eax, %ebx
	movl	%eax, 68(%rsp)
	movslq	%edi, %rax
	salq	$3, %rax
	cmpl	%ecx, %edi
	setg	%dl
	cmpl	%ebx, %edi
	movq	%rax, 80(%rsp)
	setne	%al
	andl	%eax, %edx
	leal	(%rdi,%rdi), %eax
	movl	%eax, 64(%rsp)
	leal	-1(%rcx), %eax
	movb	%dl, 55(%rsp)
	shrl	$2, %eax
	leal	0(,%rax,4), %eax
	movq	%rax, 40(%rsp)
.L170:
	movslq	24(%rsp), %r12
	movl	%r10d, 104(%rsp)
	leal	(%r12,%r12,2), %ebx
	movl	%ebx, %edi
	movl	%ebx, 12(%rsp)
	movl	%ebx, 24(%rsp)
	call	_Z16get_cos_twiddlesi
	movl	%ebx, %edi
	movq	%rax, 112(%rsp)
	call	_Z16get_sin_twiddlesi
	movl	16(%rsp), %edx
	movl	104(%rsp), %r10d
	movq	%rax, %r9
	imull	%r12d, %edx
	leal	(%rdx,%rdx), %ecx
	movl	%ecx, 124(%rsp)
	testl	%r10d, %r10d
	jle	.L160
	leal	0(,%rdx,4), %ebx
	movslq	%ecx, %rax
	movslq	%ebx, %rbx
	leaq	0(,%rax,8), %r15
	salq	$3, %rbx
	testl	%r12d, %r12d
	jle	.L160
	addl	%ecx, %edx
	movq	112(%rsp), %r8
	xorl	%esi, %esi
	movl	%r10d, 32(%rsp)
	leal	(%rdx,%rdx), %eax
	movl	%eax, 28(%rsp)
	leaq	0(,%r12,8), %rax
	xorl	%r12d, %r12d
	movq	%rax, 56(%rsp)
.L162:
	movl	%r12d, %ecx
	xorl	%eax, %eax
	movl	%esi, 48(%rsp)
	movl	%r12d, 36(%rsp)
	.p2align 4
	.p2align 3
.L169:
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff, %rdi
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff, %rsi
	vmovsd	(%r8,%rax), %xmm0
	movq	%fs:(%rdi), %r10
	vmovsd	%xmm0, 8(%r10)
	vmovsd	(%r9,%rax), %xmm0
	movq	%fs:(%rsi), %rdx
	movl	120(%rsp), %esi
	vmovsd	%xmm0, 8(%rdx)
	vmovsd	(%r8,%rax,2), %xmm0
	vmovsd	%xmm0, 16(%r10)
	vmovsd	(%r9,%rax,2), %xmm0
	vmovsd	%xmm0, 16(%rdx)
	testl	%esi, %esi
	jle	.L163
	movq	72(%rsp), %rdi
	movslq	%ecx, %r11
	movl	%ecx, 112(%rsp)
	movq	%r8, 104(%rsp)
	leaq	0(,%r11,8), %rsi
	movq	%r9, 96(%rsp)
	movq	%rax, 88(%rsp)
	movq	80(%rsp), %r14
	leaq	(%rdi,%rsi), %r13
	addq	%r14, %rsi
	leaq	(%rdi,%rsi), %r14
	movq	40(%rsp), %rsi
	addq	%rsi, %r11
	leaq	(%rdi,%r11,8), %r12
	jmp	.L164
	.p2align 4
	.p2align 3
.L186:
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff, %rax
	addq	$32, %r13
	movq	%fs:(%rax), %rdx
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff, %rax
	movq	%fs:(%rax), %r10
.L164:
	vbroadcastsd	8(%r10), %ymm2
	vbroadcastsd	8(%rdx), %ymm0
	movq	%r14, %rsi
	movq	%r13, %rdi
	vmulpd	0(%r13,%r15), %ymm2, %ymm1
	vfnmadd231pd	(%r14,%r15), %ymm0, %ymm1
	vmulpd	0(%r13,%r15), %ymm0, %ymm0
	vfmadd231pd	(%r14,%r15), %ymm2, %ymm0
	vmovupd	%ymm1, 0(%r13,%r15)
	vmovupd	%ymm0, (%r14,%r15)
	vbroadcastsd	16(%r10), %ymm2
	vbroadcastsd	16(%rdx), %ymm0
	vmulpd	0(%r13,%rbx), %ymm2, %ymm1
	movl	124(%rsp), %edx
	vfnmadd231pd	(%r14,%rbx), %ymm0, %ymm1
	vmulpd	0(%r13,%rbx), %ymm0, %ymm0
	vfmadd231pd	(%r14,%rbx), %ymm2, %ymm0
	vmovupd	%ymm1, 0(%r13,%rbx)
	vmovupd	%ymm0, (%r14,%rbx)
	vzeroupper
	call	_Z9butterflyI4v4dfLi3EEvPdS1_i
	addq	$32, %r14
	cmpq	%r12, %r13
	jne	.L186
	movl	112(%rsp), %ecx
	movq	104(%rsp), %r8
	movq	96(%rsp), %r9
	movq	88(%rsp), %rax
.L163:
	movl	68(%rsp), %edi
	cmpl	%edi, 120(%rsp)
	jl	.L187
	cmpb	$0, 55(%rsp)
	jne	.L188
.L166:
	movl	64(%rsp), %esi
	addq	$8, %rax
	addl	%esi, %ecx
	cmpq	%rax, 56(%rsp)
	jne	.L169
	movl	28(%rsp), %eax
	movl	36(%rsp), %r12d
	movl	48(%rsp), %esi
	addl	%eax, %r12d
	movl	32(%rsp), %eax
	incl	%esi
	cmpl	%eax, %esi
	jne	.L162
	movl	%eax, %r10d
.L160:
	movslq	%r10d, %rax
	movl	%r10d, %edx
	movl	20(%rsp), %ecx
	imulq	$1431655766, %rax, %rax
	sarl	$31, %edx
	shrq	$32, %rax
	movl	%eax, %r10d
	subl	%edx, %r10d
	cmpl	%ecx, 12(%rsp)
	jl	.L170
.L179:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L187:
	.cfi_restore_state
	movq	%rax, 88(%rsp)
	movl	120(%rsp), %eax
	movq	%r9, 96(%rsp)
	movq	%r8, 104(%rsp)
	movl	%ecx, 112(%rsp)
	leal	(%rcx,%rax), %edx
	movq	72(%rsp), %rax
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff, %rcx
	movslq	%edx, %rdx
	leaq	(%rax,%rdx,8), %rdi
	movq	80(%rsp), %rax
	leaq	(%rdi,%r15), %r10
	leaq	(%rdi,%rax), %rsi
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff, %rax
	movq	%fs:(%rax), %r11
	leaq	(%rsi,%r15), %rdx
	vmovddup	8(%r11), %xmm0
	movq	%fs:(%rcx), %r11
	vmovddup	8(%r11), %xmm2
	vmulpd	(%r10), %xmm2, %xmm1
	vfnmadd231pd	(%rdx), %xmm0, %xmm1
	vmulpd	(%r10), %xmm0, %xmm0
	vfmadd231pd	(%rdx), %xmm2, %xmm0
	vmovupd	%xmm1, (%r10)
	leaq	(%rdi,%rbx), %r10
	vmovupd	%xmm0, (%rdx)
	movq	%fs:(%rax), %r11
	leaq	(%rsi,%rbx), %rdx
	vmovddup	16(%r11), %xmm0
	movq	%fs:(%rcx), %r11
	vmovddup	16(%r11), %xmm2
	vmulpd	(%r10), %xmm2, %xmm1
	vfnmadd231pd	(%rdx), %xmm0, %xmm1
	vmulpd	(%r10), %xmm0, %xmm0
	vfmadd231pd	(%rdx), %xmm2, %xmm0
	vmovupd	%xmm1, (%r10)
	vmovupd	%xmm0, (%rdx)
	movl	124(%rsp), %edx
	call	_Z9butterflyI4v2dfLi3EEvPdS1_i
	cmpb	$0, 55(%rsp)
	movq	88(%rsp), %rax
	movq	96(%rsp), %r9
	movq	104(%rsp), %r8
	movl	112(%rsp), %ecx
	je	.L166
.L188:
	movq	%rax, 88(%rsp)
	movl	68(%rsp), %eax
	movq	%r9, 96(%rsp)
	movq	%r8, 104(%rsp)
	movl	%ecx, 112(%rsp)
	leal	(%rax,%rcx), %edx
	movq	72(%rsp), %rax
	movslq	%edx, %rdx
	leaq	(%rax,%rdx,8), %rdi
	movq	80(%rsp), %rax
	leaq	(%rdi,%r15), %r10
	vmovsd	(%r10), %xmm0
	leaq	(%rdi,%rax), %rsi
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff, %rax
	movq	%fs:(%rax), %r12
	movq	$_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff, %rax
	leaq	(%rsi,%r15), %rdx
	movq	%fs:(%rax), %r11
	vmovsd	(%rdx), %xmm1
	vmovsd	8(%r12), %xmm4
	vmovsd	8(%r11), %xmm3
	vmulsd	%xmm3, %xmm1, %xmm2
	vmulsd	%xmm4, %xmm1, %xmm1
	vfmsub231sd	%xmm4, %xmm0, %xmm2
	vfmadd132sd	%xmm3, %xmm1, %xmm0
	vmovsd	%xmm2, (%r10)
	vmovsd	%xmm0, (%rdx)
	leaq	(%rsi,%rbx), %rdx
	vmovsd	16(%r12), %xmm4
	leaq	(%rdi,%rbx), %r10
	vmovsd	(%rdx), %xmm1
	vmovsd	16(%r11), %xmm3
	vmovsd	(%r10), %xmm0
	vmulsd	%xmm3, %xmm1, %xmm2
	vmulsd	%xmm4, %xmm1, %xmm1
	vfmsub231sd	%xmm4, %xmm0, %xmm2
	vfmadd132sd	%xmm3, %xmm1, %xmm0
	vmovsd	%xmm2, (%r10)
	vmovsd	%xmm0, (%rdx)
	movl	124(%rsp), %edx
	call	_Z9butterflyILi3EEvPdS0_i
	movq	88(%rsp), %rax
	movq	96(%rsp), %r9
	movq	104(%rsp), %r8
	movl	112(%rsp), %ecx
	jmp	.L166
.L181:
	movq	%fs:0, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff+16
	movb	$1, %fs:_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff
	vmovdqu	%xmm0, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff
	movl	$__dso_handle, %edx
	movl	$_ZNSt6vectorIdSaIdEED1Ev, %edi
	leaq	_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff(%rax), %rsi
	call	__cxa_thread_atexit
	cmpb	$0, %fs:_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff
	jne	.L154
.L182:
	movq	%fs:0, %rax
	vpxor	%xmm0, %xmm0, %xmm0
	movl	$__dso_handle, %edx
	movl	$_ZNSt6vectorIdSaIdEED1Ev, %edi
	vmovdqu	%xmm0, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff
	movq	$0, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff+16
	movb	$1, %fs:_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff
	leaq	_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff(%rax), %rsi
	call	__cxa_thread_atexit
	jmp	.L154
.L185:
	addq	$24, %rax
	cmpq	%rax, %rcx
	je	.L158
	movq	%rax, %fs:_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff+8
	jmp	.L158
.L184:
	movq	%fs:0, %rax
	sarq	$3, %rdx
	movl	$3, %esi
	subq	%rdx, %rsi
	leaq	_ZZ12fft_1d_batchILi3EEvPdiiE2wi@tpoff(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	jmp	.L158
.L183:
	movq	%fs:0, %rax
	sarq	$3, %rdx
	movl	$3, %esi
	subq	%rdx, %rsi
	leaq	_ZZ12fft_1d_batchILi3EEvPdiiE2wr@tpoff(%rax), %rdi
	call	_ZNSt6vectorIdSaIdEE17_M_default_appendEm
	jmp	.L156
	.cfi_endproc
.LFE10057:
	.size	_Z12fft_1d_batchILi3EEvPdii, .-_Z12fft_1d_batchILi3EEvPdii
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC11:
	.string	"cannot create std::vector larger than max_size()"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4
	.globl	_Z8fft_1d_3PSt7complexIdEi
	.type	_Z8fft_1d_3PSt7complexIdEi, @function
_Z8fft_1d_3PSt7complexIdEi:
.LFB9674:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA9674
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	movq	%rsp, %rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movl	%esi, %ebx
	subq	$160, %rsp
	movq	%rdi, -112(%rbp)
	movl	%esi, -88(%rbp)
	call	_ZNSt6chrono3_V212system_clock3nowEv
	vxorpd	%xmm6, %xmm6, %xmm6
	vcvtsi2sdl	%ebx, %xmm6, %xmm0
	movq	%rax, -200(%rbp)
	call	log
	vdivsd	.LC10(%rip), %xmm0, %xmm0
	call	lround
	leal	1(%rax), %r13d
	movq	%rax, %rbx
	sarl	%r13d
	movslq	%r13d, %rax
	subl	%r13d, %ebx
	movq	%rax, %rdx
	movq	%rax, -152(%rbp)
	movabsq	$2305843009213693951, %rax
	cmpq	%rdx, %rax
	jb	.L192
	cmpq	$0, -152(%rbp)
	movslq	%ebx, %r12
	je	.L282
	salq	$2, -152(%rbp)
	movq	-152(%rbp), %r15
	movq	%r15, %rdi
.LEHB3:
	call	_Znwm
.LEHE3:
	movq	%rax, %rcx
	movq	%rax, -176(%rbp)
	leaq	-4(%r15), %rax
	movq	%rax, %rsi
	shrq	$2, %rsi
	cmpq	$24, %rax
	movq	%rcx, %rax
	leaq	1(%rsi), %rdi
	jbe	.L236
	movq	%rdi, %rdx
	shrq	$3, %rdx
	salq	$5, %rdx
	addq	%rcx, %rdx
	movl	$3, %ecx
	vmovd	%ecx, %xmm0
	vpbroadcastd	%xmm0, %ymm0
	.p2align 4
	.p2align 3
.L195:
	vmovdqu	%ymm0, (%rax)
	addq	$32, %rax
	cmpq	%rdx, %rax
	jne	.L195
	movq	-176(%rbp), %rax
	movq	%rdi, %rdx
	andq	$-8, %rdx
	andl	$7, %edi
	leaq	(%rax,%rdx,4), %rax
	je	.L283
	vzeroupper
.L194:
	subq	%rdx, %rsi
	leaq	1(%rsi), %rcx
	cmpq	$2, %rsi
	jbe	.L197
	movl	$3, %edi
	vmovd	%edi, %xmm0
	movq	-176(%rbp), %rdi
	vpshufd	$0, %xmm0, %xmm0
	vmovdqu	%xmm0, (%rdi,%rdx,4)
	movq	%rcx, %rdx
	andq	$-4, %rdx
	andl	$3, %ecx
	leaq	(%rax,%rdx,4), %rax
	je	.L196
.L197:
	movq	-176(%rbp), %rdi
	movq	-152(%rbp), %rdx
	leaq	4(%rax), %rcx
	movl	$3, (%rax)
	addq	%rdi, %rdx
	cmpq	%rcx, %rdx
	je	.L196
	leaq	8(%rax), %rcx
	movl	$3, 4(%rax)
	cmpq	%rcx, %rdx
	je	.L196
	movl	$3, 8(%rax)
.L196:
	movq	%r12, %rax
	shrq	$61, %rax
	jne	.L284
.L193:
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, -64(%rbp)
	vmovdqa	%xmm0, -80(%rbp)
	testq	%r12, %r12
	je	.L199
	salq	$2, %r12
	movq	%r12, %rdi
.LEHB4:
	call	_Znwm
.LEHE4:
	leaq	(%rax,%r12), %rdi
	subq	$4, %r12
	movq	%rax, %rcx
	movq	%r12, %r8
	movq	%rax, -80(%rbp)
	movq	%rdi, -64(%rbp)
	shrq	$2, %r8
	leaq	1(%r8), %r9
	cmpq	$24, %r12
	jbe	.L285
	movq	%r9, %rdx
	movl	$3, %esi
	shrq	$3, %rdx
	vmovd	%esi, %xmm0
	salq	$5, %rdx
	vpbroadcastd	%xmm0, %ymm0
	addq	%rax, %rdx
	.p2align 4
	.p2align 3
.L205:
	vmovdqu	%ymm0, (%rax)
	addq	$32, %rax
	cmpq	%rax, %rdx
	jne	.L205
	movq	%r9, %rdx
	andq	$-8, %rdx
	andl	$7, %r9d
	leaq	(%rcx,%rdx,4), %rax
	je	.L286
	vzeroupper
.L204:
	subq	%rdx, %r8
	leaq	1(%r8), %rsi
	cmpq	$2, %r8
	jbe	.L208
	movl	$3, %r11d
	vmovd	%r11d, %xmm0
	vpshufd	$0, %xmm0, %xmm0
	vmovdqu	%xmm0, (%rcx,%rdx,4)
	movq	%rsi, %rdx
	andq	$-4, %rdx
	andl	$3, %esi
	leaq	(%rax,%rdx,4), %rax
	je	.L206
.L208:
	leaq	4(%rax), %rdx
	movl	$3, (%rax)
	cmpq	%rdx, %rdi
	je	.L206
	leaq	8(%rax), %rdx
	movl	$3, 4(%rax)
	cmpq	%rdx, %rdi
	je	.L206
	movl	$3, 8(%rax)
.L206:
	movq	.LC14(%rip), %rax
	vxorpd	%xmm5, %xmm5, %xmm5
	movq	%rdi, -72(%rbp)
	vcvtsi2sdl	%r13d, %xmm5, %xmm1
	vmovq	%rax, %xmm0
	call	pow
	call	lround
	vxorpd	%xmm5, %xmm5, %xmm5
	movq	%rax, -160(%rbp)
	movl	%eax, %r14d
	movl	%eax, -84(%rbp)
	movq	.LC14(%rip), %rax
	vcvtsi2sdl	%ebx, %xmm5, %xmm1
	vmovq	%rax, %xmm0
	call	pow
	call	lround
	movl	%r14d, %esi
	movl	%eax, %edi
	movq	%rax, %r13
	movq	%rax, -168(%rbp)
	movl	%eax, %r15d
.LEHB5:
	call	_Z22get_6step_cos_twiddlesii
	movl	%r14d, %esi
	movl	%r13d, %edi
	movq	%rax, %rbx
	call	_Z22get_6step_sin_twiddlesii
	movq	-112(%rbp), %rdi
	movl	%r14d, %ecx
	movl	%r13d, %edx
	leaq	-80(%rbp), %rsi
	movq	%rax, %r12
	call	_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii
	testl	%r13d, %r13d
	jle	.L214
	movl	-160(%rbp), %eax
	movq	-112(%rbp), %r14
	xorl	%r13d, %r13d
	addl	%eax, %eax
	cltq
	salq	$3, %rax
	movq	%rax, -96(%rbp)
	.p2align 4
	.p2align 3
.L213:
	movl	-84(%rbp), %esi
	movq	%r14, %rdi
	call	_Z13inv_perf_shufPdi
	movq	-96(%rbp), %rax
	incl	%r13d
	addq	%rax, %r14
	cmpl	%r13d, %r15d
	jne	.L213
.L214:
	movl	-84(%rbp), %edx
	movq	-112(%rbp), %rdi
	movl	%r15d, %esi
	call	_Z12fft_1d_batchILi3EEvPdii
	movq	-160(%rbp), %rdi
	movl	%edi, %edx
	movl	%edi, %eax
	movl	%edi, %r10d
	sarl	$31, %edx
	shrl	$30, %edx
	addl	%edx, %eax
	andl	$3, %eax
	subl	%edx, %eax
	movl	-168(%rbp), %edx
	subl	%eax, %r10d
	movl	%edi, %eax
	shrl	$31, %eax
	addl	%edi, %eax
	andl	$-2, %eax
	movl	%eax, %r11d
	testl	%edx, %edx
	jle	.L225
	movslq	%edi, %rsi
	movslq	%r10d, %rax
	leal	(%rdi,%rdi), %r13d
	movl	%r15d, -204(%rbp)
	salq	$3, %rsi
	cmpl	%r10d, %edi
	leaq	0(,%rax,8), %r14
	movq	%rax, -136(%rbp)
	setg	%dl
	cmpl	%r11d, %edi
	movq	-112(%rbp), %rdi
	movq	%r14, -144(%rbp)
	setne	%al
	xorl	%ecx, %ecx
	andl	%eax, %edx
	movslq	%r11d, %rax
	movq	%rax, -184(%rbp)
	salq	$3, %rax
	movb	%dl, -96(%rbp)
	xorl	%edx, %edx
	movq	%rax, -192(%rbp)
	movq	-168(%rbp), %rax
	decl	%eax
	leaq	3(%rax,%rax,2), %rax
	salq	$3, %rax
	movq	%rax, -104(%rbp)
	leal	-1(%r10), %eax
	shrl	$2, %eax
	leal	0(,%rax,4), %eax
	movq	%rax, -120(%rbp)
	leaq	32(%rdi), %rax
	movq	%rax, -128(%rbp)
	.p2align 4
	.p2align 3
.L217:
	testl	%r10d, %r10d
	jle	.L223
	movq	-120(%rbp), %r15
	movslq	%edx, %r8
	leaq	(%rdi,%r8,8), %rax
	movq	%rax, %r9
	addq	%r15, %r8
	movq	-128(%rbp), %r15
	leaq	(%r15,%r8,8), %r15
	.p2align 4
	.p2align 3
.L218:
	movq	(%rbx), %r14
	movq	%rax, %r8
	addq	$32, %rax
	subq	%r9, %r8
	movq	(%r14,%rcx), %r14
	vmovupd	(%r14,%r8), %ymm2
	movq	(%r12), %r14
	vmulpd	-32(%rax), %ymm2, %ymm1
	movq	(%r14,%rcx), %r14
	vmovupd	(%r14,%r8), %ymm0
	vfnmadd231pd	-32(%rax,%rsi), %ymm0, %ymm1
	vmulpd	-32(%rax), %ymm0, %ymm0
	vfmadd231pd	-32(%rax,%rsi), %ymm2, %ymm0
	vmovupd	%ymm1, -32(%rax)
	vmovupd	%ymm0, -32(%rax,%rsi)
	cmpq	%r15, %rax
	jne	.L218
.L223:
	cmpl	%r11d, %r10d
	jge	.L219
	movq	-136(%rbp), %r9
	movslq	%edx, %rax
	movq	-144(%rbp), %r15
	addq	%r9, %rax
	movq	(%rbx), %r9
	leaq	(%rdi,%rax,8), %rax
	leaq	(%rax,%rsi), %r8
	movq	(%r9,%rcx), %r9
	vmovupd	(%r9,%r15), %xmm2
	movq	(%r12), %r9
	vmulpd	(%rax), %xmm2, %xmm1
	movq	(%r9,%rcx), %r9
	vmovupd	(%r9,%r15), %xmm0
	vfnmadd231pd	(%r8), %xmm0, %xmm1
	vmulpd	(%rax), %xmm0, %xmm0
	vfmadd231pd	(%r8), %xmm2, %xmm0
	vmovupd	%xmm1, (%rax)
	vmovupd	%xmm0, (%r8)
.L219:
	cmpb	$0, -96(%rbp)
	jne	.L287
.L220:
	movq	-104(%rbp), %rax
	addq	$24, %rcx
	addl	%r13d, %edx
	cmpq	%rax, %rcx
	jne	.L217
	movslq	%r13d, %r13
	xorl	%ebx, %ebx
	movl	-204(%rbp), %r15d
	movq	-112(%rbp), %r12
	salq	$3, %r13
	vzeroupper
	.p2align 4
	.p2align 3
.L224:
	movl	-84(%rbp), %esi
	movq	%r12, %rdi
	call	_Z9perf_shufPdi
	incl	%ebx
	addq	%r13, %r12
	cmpl	%ebx, %r15d
	jne	.L224
.L225:
	movq	-168(%rbp), %rax
	movq	-112(%rbp), %rdi
	movl	%r15d, %esi
	movl	%eax, %ecx
	imull	%eax, %ecx
	movl	-88(%rbp), %eax
	cltd
	idivl	%ecx
	movl	%eax, %edx
	call	_Z9transposePSt7complexIdEii
	movq	-112(%rbp), %r14
	movl	-84(%rbp), %ecx
	movl	%r15d, %edx
	leaq	-80(%rbp), %rsi
	movq	%r14, %rdi
	call	_Z11scramble_hiISt7complexIdEEvPT_RKSt6vectorIiSaIiEEii
	movl	-160(%rbp), %eax
	testl	%eax, %eax
	jle	.L226
	movl	-168(%rbp), %ebx
	movq	%r14, %r12
	movq	%r14, %r13
	xorl	%r14d, %r14d
	addl	%ebx, %ebx
	movslq	%ebx, %rbx
	salq	$3, %rbx
	jmp	.L227
	.p2align 4
	.p2align 3
.L238:
	movl	%eax, %r14d
.L227:
	movl	%r15d, %esi
	movq	%r13, %rdi
	call	_Z13inv_perf_shufPdi
	leal	1(%r14), %eax
	addq	%rbx, %r13
	cmpl	%eax, -84(%rbp)
	jne	.L238
	movl	-84(%rbp), %esi
	movq	-112(%rbp), %rdi
	movl	%r15d, %edx
	call	_Z12fft_1d_batchILi3EEvPdii
	xorl	%r13d, %r13d
	jmp	.L231
	.p2align 4
	.p2align 3
.L239:
	movl	%eax, %r13d
.L231:
	movl	%r15d, %esi
	movq	%r12, %rdi
	call	_Z9perf_shufPdi
	leal	1(%r13), %eax
	addq	%rbx, %r12
	cmpl	%r13d, %r14d
	jne	.L239
.L232:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	movq	-200(%rbp), %rdi
	vxorpd	%xmm7, %xmm7, %xmm7
	vxorpd	%xmm1, %xmm1, %xmm1
	subq	%rdi, %rax
	movq	-80(%rbp), %rdi
	vcvtsi2sdq	%rax, %xmm7, %xmm0
	vdivsd	.LC15(%rip), %xmm0, %xmm0
	vaddsd	%xmm1, %xmm0, %xmm7
	vmovq	%xmm7, %rbx
	testq	%rdi, %rdi
	je	.L230
	movq	-64(%rbp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm
.L230:
	movq	-176(%rbp), %rax
	testq	%rax, %rax
	je	.L243
	movq	-152(%rbp), %rsi
	movq	%rax, %rdi
	call	_ZdlPvm
.L243:
	addq	$160, %rsp
	vmovq	%rbx, %xmm0
	popq	%rbx
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L287:
	.cfi_restore_state
	movq	-184(%rbp), %r9
	movslq	%edx, %rax
	movq	-192(%rbp), %r15
	addq	%r9, %rax
	movq	(%rbx), %r9
	leaq	(%rdi,%rax,8), %rax
	leaq	(%rax,%rsi), %r8
	vmovsd	(%rax), %xmm3
	vmovsd	(%r8), %xmm4
	movq	(%r9,%rcx), %r9
	vmovsd	(%r9,%r15), %xmm1
	movq	(%r12), %r9
	movq	(%r9,%rcx), %r9
	vmovsd	(%r9,%r15), %xmm0
	vmulsd	%xmm4, %xmm0, %xmm2
	vfmsub231sd	%xmm3, %xmm1, %xmm2
	vmulsd	%xmm4, %xmm1, %xmm1
	vfmadd132sd	%xmm3, %xmm1, %xmm0
	vmovsd	%xmm2, (%rax)
	vmovsd	%xmm0, (%r8)
	jmp	.L220
.L282:
	cmpq	%r12, %rax
	jb	.L192
	movq	$0, -176(%rbp)
	jmp	.L193
.L199:
	movq	$0, -80(%rbp)
	movq	$0, -64(%rbp)
	xorl	%edi, %edi
	jmp	.L206
.L226:
	movl	-84(%rbp), %esi
	movq	-112(%rbp), %rdi
	movl	%r15d, %edx
	call	_Z12fft_1d_batchILi3EEvPdii
.LEHE5:
	jmp	.L232
.L286:
	vzeroupper
	jmp	.L206
.L283:
	vzeroupper
	jmp	.L196
.L236:
	xorl	%edx, %edx
	jmp	.L194
.L285:
	xorl	%edx, %edx
	jmp	.L204
.L192:
	movl	$.LC11, %edi
.LEHB6:
	call	_ZSt20__throw_length_errorPKc
.LEHE6:
.L284:
	movl	$.LC11, %edi
.LEHB7:
	call	_ZSt20__throw_length_errorPKc
.LEHE7:
.L240:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L201
.L241:
	movq	%rax, %rbx
	jmp	.L234
.L242:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L203
	.section	.gcc_except_table,"a",@progbits
.LLSDA9674:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9674-.LLSDACSB9674
.LLSDACSB9674:
	.uleb128 .LEHB3-.LFB9674
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB9674
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L240-.LFB9674
	.uleb128 0
	.uleb128 .LEHB5-.LFB9674
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L241-.LFB9674
	.uleb128 0
	.uleb128 .LEHB6-.LFB9674
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB9674
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L242-.LFB9674
	.uleb128 0
.LLSDACSE9674:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC9674
	.type	_Z8fft_1d_3PSt7complexIdEi.cold, @function
_Z8fft_1d_3PSt7complexIdEi.cold:
.LFSB9674:
.L234:
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	.cfi_escape 0x10,0x6,0x2,0x76,0
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	movq	-80(%rbp), %rdi
	movq	-64(%rbp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L280
	vzeroupper
	call	_ZdlPvm
.L201:
	cmpq	$0, -176(%rbp)
	je	.L202
.L203:
	movq	-152(%rbp), %rsi
	movq	-176(%rbp), %rdi
	call	_ZdlPvm
.L202:
	movq	%rbx, %rdi
.LEHB8:
	call	_Unwind_Resume
.LEHE8:
.L280:
	vzeroupper
	jmp	.L201
	.cfi_endproc
.LFE9674:
	.section	.gcc_except_table
.LLSDAC9674:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC9674-.LLSDACSBC9674
.LLSDACSBC9674:
	.uleb128 .LEHB8-.LCOLDB17
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
.LLSDACSEC9674:
	.section	.text.unlikely
	.text
	.size	_Z8fft_1d_3PSt7complexIdEi, .-_Z8fft_1d_3PSt7complexIdEi
	.section	.text.unlikely
	.size	_Z8fft_1d_3PSt7complexIdEi.cold, .-_Z8fft_1d_3PSt7complexIdEi.cold
.LCOLDE17:
	.text
.LHOTE17:
	.weak	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi
	.section	.tbss._ZGVZ12fft_1d_batchILi3EEvPdiiE2wi,"awTG",@nobits,_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi,comdat
	.align 8
	.type	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi, @gnu_unique_object
	.size	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi, 8
_ZGVZ12fft_1d_batchILi3EEvPdiiE2wi:
	.zero	8
	.weak	_ZZ12fft_1d_batchILi3EEvPdiiE2wi
	.section	.tbss._ZZ12fft_1d_batchILi3EEvPdiiE2wi,"awTG",@nobits,_ZZ12fft_1d_batchILi3EEvPdiiE2wi,comdat
	.align 8
	.type	_ZZ12fft_1d_batchILi3EEvPdiiE2wi, @gnu_unique_object
	.size	_ZZ12fft_1d_batchILi3EEvPdiiE2wi, 24
_ZZ12fft_1d_batchILi3EEvPdiiE2wi:
	.zero	24
	.weak	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr
	.section	.tbss._ZGVZ12fft_1d_batchILi3EEvPdiiE2wr,"awTG",@nobits,_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr,comdat
	.align 8
	.type	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr, @gnu_unique_object
	.size	_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr, 8
_ZGVZ12fft_1d_batchILi3EEvPdiiE2wr:
	.zero	8
	.weak	_ZZ12fft_1d_batchILi3EEvPdiiE2wr
	.section	.tbss._ZZ12fft_1d_batchILi3EEvPdiiE2wr,"awTG",@nobits,_ZZ12fft_1d_batchILi3EEvPdiiE2wr,comdat
	.align 8
	.type	_ZZ12fft_1d_batchILi3EEvPdiiE2wr, @gnu_unique_object
	.size	_ZZ12fft_1d_batchILi3EEvPdiiE2wr, 24
_ZZ12fft_1d_batchILi3EEvPdiiE2wr:
	.zero	24
	.section	.tbss,"awT",@nobits
	.align 8
	.type	_ZGVZ9perf_shufPdiE4tmpy, @object
	.size	_ZGVZ9perf_shufPdiE4tmpy, 8
_ZGVZ9perf_shufPdiE4tmpy:
	.zero	8
	.align 16
	.type	_ZZ9perf_shufPdiE4tmpy, @object
	.size	_ZZ9perf_shufPdiE4tmpy, 24
_ZZ9perf_shufPdiE4tmpy:
	.zero	24
	.align 8
	.type	_ZGVZ9perf_shufPdiE4tmpx, @object
	.size	_ZGVZ9perf_shufPdiE4tmpx, 8
_ZGVZ9perf_shufPdiE4tmpx:
	.zero	8
	.align 16
	.type	_ZZ9perf_shufPdiE4tmpx, @object
	.size	_ZZ9perf_shufPdiE4tmpx, 24
_ZZ9perf_shufPdiE4tmpx:
	.zero	24
	.align 8
	.type	_ZGVZ13inv_perf_shufPdiE3tmp, @object
	.size	_ZGVZ13inv_perf_shufPdiE3tmp, 8
_ZGVZ13inv_perf_shufPdiE3tmp:
	.zero	8
	.align 16
	.type	_ZZ13inv_perf_shufPdiE3tmp, @object
	.size	_ZZ13inv_perf_shufPdiE3tmp, 24
_ZZ13inv_perf_shufPdiE3tmp:
	.zero	24
	.set	.LC3,.LC8+8
	.set	.LC5,.LC9+8
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC8:
	.long	0
	.long	1072693248
	.long	-4
	.long	-1075838977
	.align 16
.LC9:
	.long	0
	.long	0
	.long	-396866389
	.long	1072412282
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC10:
	.long	2058158859
	.long	1072796650
	.align 8
.LC14:
	.long	0
	.long	1074266112
	.align 8
.LC15:
	.long	0
	.long	1104006501
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits

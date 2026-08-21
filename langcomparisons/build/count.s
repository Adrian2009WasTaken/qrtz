	.file	"counttom.c"
	.text
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	stp	x29, x30, [sp, #-48]!           // 16-byte Folded Spill
	.cfi_def_cfa_offset 48
	str	x21, [sp, #16]                  // 8-byte Folded Spill
	stp	x20, x19, [sp, #32]             // 16-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 48
	.cfi_offset w19, -8
	.cfi_offset w20, -16
	.cfi_offset w21, -32
	.cfi_offset w30, -40
	.cfi_offset w29, -48
	adrp	x20, number
	mov	w21, #16960                     // =0x4240
	ldr	w1, [x20, :lo12:number]
	movk	w21, #15, lsl #16
	cmp	w1, w21
	b.eq	.LBB0_3
// %bb.1:
	adrp	x19, .L.str
	add	x19, x19, :lo12:.L.str
.LBB0_2:                                // =>This Inner Loop Header: Depth=1
	mov	x0, x19
	bl	printf
	ldr	w8, [x20, :lo12:number]
	add	w1, w8, #1
	cmp	w1, w21
	str	w1, [x20, :lo12:number]
	b.ne	.LBB0_2
.LBB0_3:
	mov	w0, wzr
	.cfi_def_cfa wsp, 48
	ldp	x20, x19, [sp, #32]             // 16-byte Folded Reload
	ldr	x21, [sp, #16]                  // 8-byte Folded Reload
	ldp	x29, x30, [sp], #48             // 16-byte Folded Reload
	.cfi_def_cfa_offset 0
	.cfi_restore w19
	.cfi_restore w20
	.cfi_restore w21
	.cfi_restore w30
	.cfi_restore w29
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.type	number,@object                  // @number
	.bss
	.globl	number
	.p2align	2, 0x0
number:
	.word	0                               // 0x0
	.size	number, 4

	.type	.L.str,@object                  // @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d\n"
	.size	.L.str, 4

	.ident	"clang version 21.1.8"
	.section	".note.GNU-stack","",@progbits

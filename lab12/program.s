	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 14, 0
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	w8, #5
	str	w8, [sp, #12]
	str	w8, [sp, #8]
	mov	w8, #6
	str	w8, [sp, #4]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	mul	w8, w8, w9
	ldr	w9, [sp, #4]
	mul	w8, w8, w9
	str	w8, [sp, #8]
	mov	w0, #0
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols

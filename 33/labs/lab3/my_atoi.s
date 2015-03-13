	.file	"my_atoi.c"
	.text       # Begins a text section - code lives here.

.globl my_atoi  # defines the _main symbol as global, visible to the linker and other modules
	.type	my_atoi, @function

my_atoi:
    # IMPORTANT
    # topmost stack frame delimited/bounded by ebp's (base stack frame pointer) and esp's (stack
    # pointer) values, so these register values don't have to be saved to stack while this procedure
    # is stack's topmost, current procedure

	pushq	%rbp         # save the parent caller's base pointer value to restore to ebp when callee
                         # terminates, so push current ebp value on the stack - this will rest at
                         # base of callee's stack frame

	movq	%rsp, %rbp   # delimit current procedure (callee) atoi's stack frame (stack's topmost) by
                         # setting ebp value to current esp. esp will change as stack grows further.
                         # So ebp base frame pointer register value points to the ebp value we just
                         # pushed onto the stack and sets the base of this stack frame.

    # callee pushes following registers onto stack for restoration at end of atoi
	pushq	%rbx
	pushq	%rdi
	pushq	%rsi
##############################
# DON'T EDIT ABOVE THIS LINE #
##############################
#
# atoi
#
# Make sure your return value is in the %rax register at the end!

    movq $0, %rax       # rax must contain return value, so it is accumulator, set to 0
    movq 16(%rbp), %rdx # skip return address (8 bytes above atoi's base stack frame
	                    # pointer) to access arg char* (16 bytes above base stack
	                    # frame pointer stored in ebp register), place at edx

ITER:
    movzbq (%rdx), %rcx # ecx takes decimal value from pointer, each acii character is 1 byte
    subq $48, %rcx      # retrieve integer value of digit char
    cmpq $9, %rcx       # determine if character is a digit or not, 9 - ecx
    ja  FIN             # if character is not a digit, terminate by jumping to FIN
    imulq $10, %rax     # accumulator *= 10
    addq %rcx, %rax     # accumulator + (integer represented by character)
    incq %rdx           # move to next character in array, edx++
    jmp ITER            # continue iterating
FIN:

##############################
# DON'T EDIT BELOW THIS LINE #
##############################
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movq	-8(%rbp), %rbx
	leave
	ret
	.size	my_atoi, .-my_atoi
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
	.section	.note.GNU-stack,"",@progbits

	.file	"my_atoi.c"
	.text       # Begins a text section - code lives here.

.globl my_atoi  # defines the _main symbol as global, visible to the linker and other modules
	.type	my_atoi, @function

my_atoi:
    # IMPORTANT
    # topmost stack frame delimited/bounded by ebp's (base stack frame pointer) and esp's (stack
    # pointer) values, so these register values don't have to be saved to stack while this procedure
    # is stack's topmost, current procedure

	pushl	%ebp         # save the parent caller's base pointer value to restore to ebp when callee
                         # terminates, so push current ebp value on the stack - this will rest at
                         # base of callee's stack frame

	movl	%esp, %ebp   # delimit current procedure (callee) atoi's stack frame (stack's topmost) by
                         # setting ebp value to current esp. esp will change as stack grows further.
                         # So ebp base frame pointer register value points to the ebp value we just
                         # pushed onto the stack and sets the base of this stack frame.

    # callee pushes following registers onto stack for restoration at end of atoi
	pushl	%ebx
	pushl	%edi
	pushl	%esi
##############################
# DON'T EDIT ABOVE THIS LINE #
##############################
#
# atoi
#
# 8(%ebp) currently holds a pointer to the array of characters (string).
#
# This means that 8 bytes above the base pointer of atoi's stack frame (stack grows downwards,
# higher addresses are at the bottom of stack) is the first argument passed to atoi().
# 4 bytes above the base pointer of atoi is the caller's return address/caller instruction to
# execute when callee terminates. So we add 8 bytes to register ebp's value to access pointer
# to array of chars
#
# Abstract idea to remember is that with each new function/procedure call, arguments caller is
# passing to callee, then the return address in caller procedure, are placed on the stack. Then,
# push caller's ebp register value onto stack so ebp may be restored to this value once callee
# terminates. Then save current esp stack pointer value (pointing to the ebp value we just saved
# on the stack) to ebp register to delimit callee's base stack frame at this stack position. We
# can use ebp register's current value as a point of reference to access the caller's arguments
# lower in the stack by adding bytes to the ebp register value (an address, all memory is contiguous)
#
# ebp register value never changes as long as this callee procedure is topmost/current procedure
# running. When this callee procedure terminates, simply move ebp register value to esp, setting
# the stack pointer to beginning of this frame where we saved the caller's ebp value on stack. Pop here,
# restoring the parent's ebp we saved onto stack at start of this procedure to ebp's current value and
# esp stack pointer is now at end of the caller's frame. This way the caller becomes the topmost/current
# stack frame/procedure running, as the current ebp and esp register values delimit the caller's stack frame.
#
# In the callee's stack frame, don't confuse the saved ebp register value on the stack with the current
# ebp register value. The saved value on the stack is used to re-build/re-delimit the caller's stack frame
# from the current callee's stack frame. The current ebp register value always delimits the base of the
# current, topmost (on stack) procedure's stack frame. It can be confusing since current procedure's ebp
# register value points to the address where the caller's ebp value was saved on the stack. However, the
# stack's saved ebp value is only used to reset current procedure's ebp value to that of parent caller's.
# So, every stack frame has its parent's ebp value saved at its base to re-create the parent's stack frame
# from this child's once it terminates.
#
# Make sure your return value is in the %eax register at the end!

# Write your code here...

    movl $0, %eax       # eax must contain return value, so it is accumulator, set to 0
    movl 8(%ebp), %edx  # skip return address (4 bytes above atoi's base stack frame
	                    # pointer) to access arg char* (8 bytes above base stack
	                    # frame pointer stored in ebp register), place at edx

ITER:
    movzbl (%edx), %ecx # ecx takes decimal value from pointer, each acii character is 1 byte
    subl $48, %ecx      # to retrieve integer value of digit char, subtract 48
    cmpl $9, %ecx       # determine if character is a digit or not, 9 - ecx
    ja  FIN             # if character is not a digit, terminate by jumping to FIN
    imull $10, %eax      # accumulator *= 10
    addl %ecx, %eax     # accumulator + (integer represented by character)
    incl %edx           # move to next character in array, edx++
    jmp ITER            # continue iterating
FIN:

##############################
# DON'T EDIT BELOW THIS LINE #
##############################
	movl	-12(%ebp), %esi
	movl	-8(%ebp), %edi
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	my_atoi, .-my_atoi
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
	.section	.note.GNU-stack,"",@progbits

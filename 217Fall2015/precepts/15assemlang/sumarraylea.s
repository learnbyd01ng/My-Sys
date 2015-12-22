### --------------------------------------------------------------------
### sumarraylea.s
### Author: Bob Dondero
### --------------------------------------------------------------------

        .equ    ARRAY_LENGTH, 100

### --------------------------------------------------------------------

        .section ".rodata"

cPrompt:
        .string "How many integers?  "
cScanfFormat:
        .string "%ld"
cResult:
        .string "The sum is %ld.\n"

### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"

lNumbers:
        .skip   8 * ARRAY_LENGTH
lIndex:
        .skip   8
lCount:
        .skip   8
lSum:
        .skip   8

### --------------------------------------------------------------------

        .section ".text"

        ## -------------------------------------------------------------
        ## Read up to ARRAY_LENGTH integers from stdin, and write to
        ## stdout the sum of those integers.  Return 0.
        ## int main(void)
        ## -------------------------------------------------------------

        .globl  main
        .type   main,@function

main:

        ## printf("How many integers?  ")
        movq    $cPrompt, %rdi
        movl    $0, %eax
        call    printf

        ## scanf("%ld", &lCount)
        movq    $cScanfFormat, %rdi
        movq    $lCount, %rsi
        movl    $0, %eax
        call    scanf

        ## lIndex = 0
        movq    $0, lIndex

loop1:

        ## if (lIndex >= lCount) goto loopend1
        movq    lIndex, %rax
        cmpq    lCount, %rax
        jge     loopend1

        ## scanf("%ld", &alNumbers[lIndex])
        movq    $cScanfFormat, %rdi
        movq    lIndex, %rsi
        leaq    lNumbers(,%rsi,8), %rsi     # the lea instruction
        movl    $0, %eax
        call    scanf

        ## lIndex++
        incq    lIndex

        ## goto loop1
        jmp     loop1

loopend1:

        ## lSum = 0
        movq    $0, lSum

        ## lIndex = 0
        movq    $0, lIndex

loop2:

        ## if (lIndex >= lCount) goto loopend2
        movq    lIndex, %rax
        cmpq    lCount, %rax
        jge     loopend2

        ## lSum += alNumbers[lIndex]
        movq    lIndex, %rax
        movq    lNumbers(,%rax,8), %rax     # scaled indexed addressing
        addq    %rax, lSum

        ## lIndex++
        incq    lIndex

        ## goto loop2
        jmp     loop2

loopend2:

        ## printf("The sum is %ld.\n", lSum)
        movq    $cResult, %rdi
        movq    lSum, %rsi
        movl    $0, %eax
        call    printf

        ## return 0
        movl    $0, %eax
        ret

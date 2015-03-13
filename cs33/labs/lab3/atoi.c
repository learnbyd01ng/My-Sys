/**
 * run 'make' to compile
 * 'gdb atoi' to start debugger
 * 'b my_aoit.s:34' to set a breakpoint
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_atoi.h"

#define INPUTSIZE 256

int main(int argc, char *argv[]) {
    char str[INPUTSIZE];
    printf("Enter an integer: ");
    while (fgets(str, INPUTSIZE, stdin) != NULL) {
        // remove pesky newline
        int len = strlen(str);
		if(str[len - 1] == '\n')
			str[len - 1] = '\0';
        printf("atoi(\"%s\") returned %d\n", str, my_atoi(str));
        printf("Enter an integer: ");
   }
    return 0;
}

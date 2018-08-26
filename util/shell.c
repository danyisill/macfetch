#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
void shell(void){
	printf("shell:  %s\n", basename(getenv("SHELL")));
}
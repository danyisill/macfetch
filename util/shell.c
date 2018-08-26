#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
char *shell(void){
	return basename(getenv("SHELL"));
}
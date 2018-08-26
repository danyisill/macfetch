#include <stdlib.h>
#include <sys/sysctl.h>
char *cpu(void){
	size_t size;
	sysctlbyname("machdep.cpu.brand_string", NULL, &size, NULL, 0);
	char *out = malloc(size);
	sysctlbyname("machdep.cpu.brand_string", out, &size, NULL, 0);
	return out;
}
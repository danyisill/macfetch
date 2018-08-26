#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>

void uptime(void){
	struct timeval boot;
	size_t len = sizeof(boot);
	sysctlbyname("kern.boottime", &boot, &len, NULL, 0);
	printf("uptime: %.4g hours\n", difftime(time(NULL), boot.tv_sec) / (60 * 60));
}
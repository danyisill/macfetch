#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>

char *uptime(void){
	struct timeval boot;
	char *out;
	size_t len = sizeof(boot);
	sysctlbyname("kern.boottime", &boot, &len, NULL, 0);
	asprintf(&out, "%.4g hours", difftime(time(NULL), boot.tv_sec) / (60 * 60));
	return out;
}
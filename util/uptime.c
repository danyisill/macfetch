#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#include <math.h>

char *uptime(void){
	struct timeval boot;
	size_t len = sizeof(boot);
	sysctlbyname("kern.boottime", &boot, &len, NULL, 0);
	unsigned minutes = (unsigned)round(difftime(time(NULL), boot.tv_sec)) / 60;
	char *out;
	asprintf(&out, "%d days, %d hours and %d minutes", minutes / (60 * 24), minutes / 60, minutes % 60);
	return out;
}
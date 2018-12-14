#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#include <math.h>
#include <stdlib.h>
char *fmt(unsigned seconds){
	char *out = malloc(64);
	size_t len = 0;
	unsigned minutes = seconds / 60,
	hours = minutes / 60,
	days = hours / 24;

	if(days)
		len += sprintf(out + len, "%dd", days);
	if(hours % 24)
		len += sprintf(out + len, "%dh", hours % 24);
	if(minutes % 60)
		len += sprintf(out + len, "%dm", minutes % 60);
	if(seconds % 60)
		len += sprintf(out + len, "%ds", seconds % 60);
	return out;
}
char *uptime(void){
	struct timeval boot;
	size_t size = sizeof(boot);
	sysctlbyname("kern.boottime", &boot, &size, NULL, 0);
	return fmt(round(difftime(time(NULL), boot.tv_sec)));
}
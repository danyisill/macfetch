#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#include <math.h>
#include <stdlib.h>

char *uptime(void){
	struct timeval boot;
	size_t size = sizeof(boot),
	len = 0;
	sysctlbyname("kern.boottime", &boot, &size, NULL, 0);
	unsigned seconds = (unsigned)round(difftime(time(NULL), boot.tv_sec)),
	minutes = seconds / 60,
	hours = minutes / 60,
	days = hours / 24;
	char *out = malloc(32);
	if(days)
		len += sprintf(out + len, "%d day%s, ", days, (days == 1)?"":"s");
	if(hours)
		len += sprintf(out + len, "%d hour%s, ", hours % 24, (hours % 24 == 1)?"":"s");
	if(minutes)
		len += sprintf(out + len, "%d minute%s and ", minutes % 60, (minutes % 60 == 1)?"":"s");
	len += sprintf(out + len, "%d seconds", seconds % 60);
	return out;
}
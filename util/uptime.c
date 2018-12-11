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
	unsigned seconds = round(difftime(time(NULL), boot.tv_sec)),
	minutes = seconds / 60,
	hours = minutes / 60,
	days = hours / 24;
	char *out = malloc(64);
	if(days)
		len += sprintf(out + len, "%d day%s%s", days, (days == 1)?"":"s", (hours % 24)?", ":"");
	if(hours % 24)
		len += sprintf(out + len, "%d hour%s%s", hours % 24, (hours % 24 == 1)?"":"s", (minutes % 60)?", ":"");
	if(minutes % 60)
		len += sprintf(out + len, "%d minute%s%s", minutes % 60, (minutes % 60 == 1)?"":"s", (seconds % 60)?", ":"");
	if(seconds % 60)
		len += sprintf(out + len, "%d second%s", seconds % 60, (seconds % 60 == 1)?"":"s");
	return out;
}
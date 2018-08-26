#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>

char *model(void){
	char buf[128], *out;
	size_t len;
	sysctlbyname("hw.model", NULL, &len, NULL, 0);
	char *mod = malloc(len * sizeof(char));
	sysctlbyname("hw.model", mod, &len, NULL, 0);
	FILE *log;
	log = fopen("/var/log/system.log", "r");
	while(fgets(buf, 128, log)){
		if(strstr(buf, "akeSMC"))
			break;
	}
	asprintf(&out, "%s%s", feof(log)?"":"Hackintosh, SMBIOS = ", mod);
	return out;
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>

void model(void){
	char buf[128];
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
	if(feof(log))
		printf("model:  %s\n", mod);
	else{
		printf("model:  Hackintosh (%s SMBIOS)\n", mod);
	}
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <IOKit/kext/KextManager.h>
#include "map.h"
void _hackintosh(Map *map){
	map->model.is_hackintosh = 0;
	if(map->ver.min > 6){
		char *buf = malloc(64);
		CFStringRef values[] = {CFSTR("org.netkas.driver.FakeSMC"), CFSTR("as.vit9696.VirtualSMC")};
		CFStringRef empty_str[] = {CFSTR("")};
		map->model.is_hackintosh = CFDictionaryGetCount(KextManagerCopyLoadedKextInfo(CFArrayCreate(NULL, (const void **)values, 1, NULL), CFArrayCreate(NULL, (const void**)empty_str, 1, NULL)));
	}
}
void _model(Map *map){
	size_t len;
	sysctlbyname("hw.model", NULL, &len, NULL, 0);
	map->model.id = malloc(len);
	sysctlbyname("hw.model", map->model.id, &len, NULL, 0);
}
char *model(Map *map){
	_hackintosh(map);
	_model(map);
	char *out;
	asprintf(&out, "%s%s", map->model.is_hackintosh?"Hackintosh, SMBIOS = ":"", map->model.id);
	return out;
}
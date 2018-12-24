#include <CoreFoundation/CoreFoundation.h>
#include "map.h"
#define def CFSTR("/System/Library/CoreServices/SystemVersion")
char *codenames[] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
void _ver(struct ver *ver){
	CFArrayRef split = CFStringCreateArrayBySeparatingStrings(NULL, CFPreferencesCopyAppValue(CFSTR("ProductVersion"), def), CFSTR("."));
	ver->maj = CFStringGetIntValue(CFArrayGetValueAtIndex(split, 0));
	ver->min = CFStringGetIntValue(CFArrayGetValueAtIndex(split, 1));
	if(CFArrayGetCount(split) == 3)
		ver->fix = CFStringGetIntValue(CFArrayGetValueAtIndex(split, 2));
	else
		ver->fix = 0;
}
void _build_ver(char **build_ver){
	*build_ver = malloc(16);
	CFStringGetCString(CFPreferencesCopyAppValue(CFSTR("ProductBuildVersion"), def), *build_ver, 16, kCFStringEncodingUTF8);
}
char *ver(Map *map){
	_ver(&map->ver);
	_build_ver(&map->ver.build_ver);
	char *out;
	asprintf(&out, "%s %d.%d.%d %s (%s)", (map->ver.min < 8)?"Mac OS X":(map->ver.min < 12)?"OS X":"macOS", map->ver.maj, map->ver.min, map->ver.fix, codenames[map->ver.min - 1], map->ver.build_ver);
	return out;
}
#include <CoreFoundation/CoreFoundation.h>
#include "map.h"
#define def CFSTR("/System/Library/CoreServices/SystemVersion")
// Added recent versions
char *codenames[] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave", "Catalina", "Big Sur", "Monterey", "Ventura"};
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
char *ver(Map *map) {
  _ver(&map->ver);
  _build_ver(&map->ver.build_ver);
  char *os_name = "macOS";
  if (map->ver.maj < 10 || (map->ver.maj == 10 && map->ver.min < 8)) {
    os_name = "Mac OS X";
  }
  int codename_index = (map->ver.maj - 10) * 6 + (map->ver.min - 6);
  if (codename_index >= 0 && codename_index <= 17) {
    codename_index = codename_index >= 9 ? codename_index + 1 : codename_index;
  }
  char *codename = (codename_index >= 0 && codename_index <= 17) ? codenames[codename_index] : "";
  if (map->ver.maj == 13 && map->ver.min == 3) {
    codename = "Ventura";
  }
  char *out;
  asprintf(&out, "%s %d.%d.%d %s (%s)", os_name, map->ver.maj, map->ver.min, map->ver.fix, codename, map->ver.build_ver);
  return out;
}

#include <CoreFoundation/CoreFoundation.h>
char *codenames[] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
char *ver(void){
	CFStringRef keys[] = {CFSTR("ProductVersion"), CFSTR("ProductBuildVersion")};
	CFStringRef def = CFSTR("/System/Library/CoreServices/SystemVersion.plist");
	CFPropertyListRef values[2];
	char *ver_s[2];
	for(int i = 0; i < 2; ++i){
		ver_s[i] = malloc(16);
		values[i] = CFPreferencesCopyAppValue(keys[i], def);
		CFStringGetCString(values[i], ver_s[i], 16, kCFStringEncodingUTF8);
	}
	CFArrayRef split = CFStringCreateArrayBySeparatingStrings(NULL, (CFStringRef)values[0], CFSTR("."));
	int maj = CFStringGetIntValue(CFArrayGetValueAtIndex(split, 1));
	char *out;
	asprintf(&out, "%s %s %s (%s)", (maj < 8)?"Mac OS X":(maj < 12)?"OS X":"macOS", ver_s[0], codenames[maj - 1], ver_s[1]);
	return out;
}
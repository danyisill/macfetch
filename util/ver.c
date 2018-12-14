#include <CoreFoundation/CoreFoundation.h>
char *codenames[] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
char *ver(void){
	CFStringRef def = CFSTR("/System/Library/CoreServices/SystemVersion.plist");
	char *b_ver = malloc(32), *p_ver = malloc(32), *maj_s = malloc(4);
	CFPropertyListRef p_vcf = CFPreferencesCopyAppValue(CFSTR("ProductVersion"), def);
	CFPropertyListRef b_vcf = CFPreferencesCopyAppValue(CFSTR("ProductBuildVersion"), def);
	CFStringGetCString(b_vcf, b_ver, 32, kCFStringEncodingUTF8);
	CFStringGetCString(p_vcf, p_ver, 32, kCFStringEncodingUTF8);
	CFArrayRef split = CFStringCreateArrayBySeparatingStrings(NULL, (CFStringRef)p_vcf, CFSTR("."));
	CFStringGetCString(CFArrayGetValueAtIndex(split, 1), maj_s, 4, kCFStringEncodingUTF8);
	int maj = atoi(maj_s);
	char *out;
	asprintf(&out, "%s %s %s (%s)", (maj < 8)?"Mac OS X":(maj < 12)?"OS X":"macOS", p_ver, codenames[maj - 1], b_ver);
	return out;
}
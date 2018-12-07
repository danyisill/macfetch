#import <Foundation/Foundation.h>
char *ver(void){
	NSDictionary *p = [NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
	const char *version = [[p valueForKeyPath:@"ProductVersion"] UTF8String];
	char *out;
	int ver = [[[p valueForKeyPath:@"ProductVersion"] componentsSeparatedByString:@"."][1] intValue];
	char *code[15] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	asprintf(&out, "%s %s %s", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", version, code[ver - 1]);
	return out;
}
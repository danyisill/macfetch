#import <Foundation/Foundation.h>
char *ver(void){
	NSDictionary *p = [NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
	const char *version_string = [[p valueForKeyPath:@"ProductVersion"] UTF8String];
	char *out;
	int ver = [[[p valueForKeyPath:@"ProductVersion"] componentsSeparatedByString:@"."][1] intValue];
	char *code[14] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	asprintf(&out, "%s %s %s", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", version_string, code[ver - 1]);
	return out;
}
char *theme(void){
	NSUserDefaults *def = [NSUserDefaults standardUserDefaults];
	char *out, *accents[9] = {"Graphite", "Red", "Orange", "Yellow", "Green", "", "Purple", "Pink", "Blue"};
	asprintf(&out, "%s %s",
	([def stringForKey:@"AppleInterfaceStyle"])?"Dark":"Light",
	([[[def dictionaryRepresentation] allKeys] containsObject:@"AppleAccentColor"])?accents[[def integerForKey:@"AppleAccentColor"] + 1]:([def integerForKey:@"AppleAquaColorVariant"] == 6)?"Graphite":"Blue");
	return out;
}
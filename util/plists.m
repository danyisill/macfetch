#import <Foundation/Foundation.h>
char *codenames[] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"},
*accents[] = {"Graphite", "Red", "Orange", "Yellow", "Green", "", "Purple", "Pink", "Blue"};
const char *ver(void){
	NSString *version_string = [[NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"] valueForKeyPath:@"ProductVersion"];
	int ver = [[version_string componentsSeparatedByString:@"."][1] intValue];
	return [[NSString stringWithFormat:@"%s %@ %s", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", version_string, codenames[ver - 1]] UTF8String];
}
const char *theme(void){
	NSUserDefaults *def = [NSUserDefaults standardUserDefaults];
	return [[NSString stringWithFormat:@"%s %s", ([def objectForKey:@"AppleInterfaceStyle"])?"Dark":"Light", ([def objectForKey:@"AppleAccentColor"])?accents[[def integerForKey:@"AppleAccentColor"] + 1]:([def integerForKey:@"AppleAquaColorVariant"] == 6)?"Graphite":"Blue"] UTF8String];
}
const char *gpu(void){
	CFMutableDictionaryRef matchDict = IOServiceMatching("IOPCIDevice");
	io_iterator_t iterator;
	if (IOServiceGetMatchingServices(kIOMasterPortDefault, matchDict, &iterator) == kIOReturnSuccess){
		io_registry_entry_t regEntry;
		while ((regEntry = IOIteratorNext(iterator))) {
			CFMutableDictionaryRef serviceDictionary;
			if (IORegistryEntryCreateCFProperties(regEntry, &serviceDictionary, kCFAllocatorDefault, kNilOptions) != kIOReturnSuccess){
                	    IOObjectRelease(regEntry);
                	    continue;
                	}
                	const void *GPUModel = CFDictionaryGetValue(serviceDictionary, @"model");
                	if (GPUModel != nil) {
                	    if (CFGetTypeID(GPUModel) == CFDataGetTypeID()) 
                	        return [[[NSString alloc] initWithData:(NSData *)GPUModel encoding:NSASCIIStringEncoding] UTF8String];
                	}
                	CFRelease(serviceDictionary);
                	IOObjectRelease(regEntry);
            	}
		IOObjectRelease(iterator);
        }
	return "N/A";
}
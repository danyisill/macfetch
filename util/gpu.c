#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitlib.h>
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
                	const void *GPUModel = CFDictionaryGetValue(serviceDictionary, CFSTR("model"));
                	if (GPUModel && CFGetTypeID(GPUModel) == CFDataGetTypeID())
					return (char *)CFDataGetBytePtr((CFDataRef) GPUModel);
                	CFRelease(serviceDictionary);
                	IOObjectRelease(regEntry);
            	}
		IOObjectRelease(iterator);
        }
	return "N/A";
}
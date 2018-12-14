#include <CoreFoundation/CoreFoundation.h>
char *accents[] = {"Graphite", "Red", "Orange", "Yellow", "Green", "", "Purple", "Pink", "Blue"};
char *theme(void){
	Boolean e;
	CFStringRef def = CFSTR(".GlobalPreferences");
	CFIndex accent = CFPreferencesGetAppIntegerValue(CFSTR("AppleAccentColor"), def, &e);
	CFIndex colorvar = CFPreferencesGetAppIntegerValue(CFSTR("AppleAquaColorVariant"), def, NULL);
	CFPropertyListRef style = CFPreferencesCopyAppValue(CFSTR("AppleInterfaceStyle"), def);
	char *out;
	asprintf(&out, "%s %s", style?"Dark":"Light", e?accents[accent + 1]:colorvar == 6?"Graphite":"Blue");
	return out;
}
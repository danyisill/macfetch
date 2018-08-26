
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
struct utsname uts;
void ver(void){
	char ver = (uts.release[0] == '1')?uts.release[1] - '0' + 6:uts.release[0] - '0' - 4;
	char *code[15] = {"", "Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	printf("os:     %s 10.%d %s\n", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", ver, code[ver]);
}
void kernel(void){
	printf("kernel: %s %s %s\n", uts.machine, uts.sysname, uts.release);
}
int main(int argc, char *argv[]){
	struct {
		unsigned logo : 1;
		unsigned uh : 1;
	} pref;
	int opt;
	void (*funs[NVARS])(void) = {ver, kernel, model, cpu, fs, mem, uptime, pkgs, shell};
	uname(&uts);
	while ((opt = getopt(argc, argv, "hlu")) != -1){
		switch(opt){
			case 'h':
				puts("macfetch -hlu\n-h: display help and exit\n-l don't display logo\n-u don't display user@hostname");
				return 0;
			case 'l':
				pref.logo = 1;
				break;
			case 'u':
				pref.uh = 1;
				break;
		}
	}
	if(!pref.uh)
		printf("%s%s@%s\n", pref.logo?"":"                ", getenv("USER"), uts.nodename);
	for (int i = 0; i < NVARS; ++i){
		if(!pref.logo) printf("%s", apple[i]);
		funs[i]();
	}
	return 0;
}

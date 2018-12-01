#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
struct utsname uts;
char *ver(void){
	char *out;
	char ver = (uts.release[0] == '1')?uts.release[1] - '0' + 6:uts.release[0] - '0' - 4;
	char *code[15] = {"Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	asprintf(&out, "%s 10.%d %s", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", ver, code[ver - 1]);
	return out;
}
char *kernel(void){
	char *out;
	asprintf(&out, "%s %s %s", uts.machine, uts.sysname, uts.release);
	return out;
}
int main(int argc, char *argv[]){
	struct {
		unsigned logo : 1;
		unsigned uh : 1;
		unsigned gui : 1;
	} pref;
	int opt;
	char *(*funs[NVARS])(void) = {ver, kernel, model, cpu, fs, mem, uptime, pkgs, shell},
	*labels[NVARS] = {"os", "kernel", "model", "cpu", "disk", "memory", "uptime", "pkgs", "shell"},
	*guispaces[NVARS] = {"		", "	", "	", "		", "	", "	", "	", "	", "	"};
	uname(&uts);
	while ((opt = getopt(argc, argv, "ghlu")) != -1){
		switch(opt){
			case 'h':
				puts("macfetch -ghlu\n-g format the spacing so it aligns in the GUI dialog window\n-h: display help and exit\n-l don't display logo\n-u don't display user@hostname");
				return 0;
			case 'l':
				pref.logo = 1;
				break;
			case 'u':
				pref.uh = 1;
				break;
			case 'g':
				pref.gui = 1;
				break;
		}
	}
	if(!pref.uh)
		printf("%s%s@%s\n", pref.logo?"":"                ", getenv("USER"), uts.nodename);
	char longestelementlength = 0;
	for (int i = 0; i < NVARS; ++i)
		if(strlen(labels[i]) > longestelementlength)
			longestelementlength = strlen(labels[i]);
	char *space = malloc(longestelementlength);
	memset(space, ' ', longestelementlength);
	for (int i = 0; i < NVARS; ++i){
		if(!pref.logo) printf("%s", apple[i]);
		printf("%s: %s%s\n", labels[i], pref.gui?guispaces[i]:space + strlen(labels[i]), funs[i]());
	}
	return 0;
}

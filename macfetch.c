#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#define SIZE(a) (sizeof a / sizeof *a)

struct utsname uts;
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
	char *(*funs[])(void) = {ver, kernel, model, cpu, gpu, fs, mem, uptime, pkgs, shell, theme},
	*labels[] = {"os", "kernel", "model", "cpu", "gpu", "disk", "memory", "uptime", "pkgs", "shell", "theme"},
	*guispaces[] = {"		", "	", "	", "		", "		", "		", "	", "	", "	", "	", "	"};
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
	char longestelementlength = 0, temp = 0;
	for (int i = 0; i < SIZE(labels); ++i)
		if((temp = strlen(labels[i])) > longestelementlength)
			longestelementlength = temp;
	char *space = malloc(longestelementlength);
	memset(space, ' ', longestelementlength);
	for (int i = 0; i < SIZE(labels); ++i){
		if(!pref.logo) printf("%s", apple[i]);
		printf("%s: %s%s\n", labels[i], pref.gui?guispaces[i]:space + strlen(labels[i]), funs[i]());
	}
	return 0;
}

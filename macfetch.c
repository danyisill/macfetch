#define GIGA (1024.0 * 1024 * 1024)
#define NVARS 8

#include "apple.h"
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <sys/utsname.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <mach/mach_time.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

struct utsname uts;

void ver(void){
	char ver = (uts.release[0] == '1')?uts.release[1] - '0' + 6:uts.release[0] - '0' - 4, 
	*code[15] = {"", "Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	printf("os:     %s 10.%hhu %s\n", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", ver, code[ver]);
}
void fs(void){
	struct statfs size;
	statfs("/", &size);
	double total = (size.f_bsize * size.f_blocks) / GIGA;
	printf("disk:   %.4g / %.4g GiB\n", total - ((size.f_bsize * size.f_bavail) / GIGA), total);
}
void mem(void){
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
	KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats, &count)){
		double free = ((int64_t)vm_stats.free_count + (int64_t)vm_stats.inactive_count) * (int64_t)page_size;
		double used = ((int64_t)vm_stats.active_count + (int64_t)vm_stats.wire_count) * (int64_t)page_size;
		free /= GIGA;
		used /= GIGA;
		printf("memory: %.4g / %.4g GiB\n", used, free + used);
	}
}
void uptime(void){ //taken from screenfetch-c
	long long uptime = 0;
	static mach_timebase_info_data_t timebase_info;
	if (timebase_info.denom == 0){
		(void) mach_timebase_info(&timebase_info);
	}
	uptime = (long long)((mach_absolute_time() * timebase_info.numer) / (1000* 1000 * timebase_info.denom));
	printf("uptime: %.4g hours\n", uptime / (1000.0 * 60 * 60));
}
void pkgs(){
	glob_t gl;
	if(access("/usr/local/Cellar/", F_OK) != -1)
		glob("/usr/local/Cellar/*", GLOB_NOSORT, NULL, &gl);
	if(access("/opt/local/bin/", F_OK) != -1)
		glob("/opt/local/bin/*", GLOB_NOSORT, NULL, &gl);
	if(gl.gl_pathc)
		printf("pkgs:   %zu\n", gl.gl_pathc);
}
void kernel(){
	printf("kernel: %s %s\n", uts.sysname, uts.release);
}
void cpu(){
	size_t size;
	sysctlbyname("machdep.cpu.brand_string", NULL, &size, NULL, 0);
	char *out = malloc(size);
	sysctlbyname("machdep.cpu.brand_string", out, &size, NULL, 0);
	printf("cpu:    %s\n", out);
}
void shell(){
	printf("shell:  %s\n", basename(getenv("SHELL")));
}
int main(int argc, char *argv[]){
	uname(&uts);
	int opt;
	struct {
		unsigned logo : 1;
		unsigned uh : 1;
	} pref;
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
	void (*order[NVARS])() = {ver, kernel, cpu, fs, mem, uptime, pkgs, shell};
	if(pref.logo)
		for (int i = 0; i < NVARS; ++i)
			order[i]();
	else
		for (int i = 0; i < NVARS; ++i){
			printf("%s", apple[i]);
			order[i]();
		}
	return 0;
}
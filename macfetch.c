#define GIGA (1024.0 * 1024 * 1024)
#define GIGAI (1024 * 1024 * 1024)

#define E "\e[0m"
#define B "\e[1m"
#define G B "\e[38;5;2m"
#define O B "\e[38;5;214m"
#define D B "\e[38;5;208m"
#define R B "\e[38;5;196m"
#define M B "\e[38;5;127m"
#define F B "\e[38;5;33m"

#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

struct {
	unsigned logo : 1;
	unsigned uh : 1;
} pref;
struct utsname uts;
glob_t gl;
double disk_total, disk_used;
int opt;

char *ver(void){
	char ver = (uts.release[0] == '1')?uts.release[1] - '0' + 6:uts.release[0] - '0' - 4, 
	*code[15] = {"", "Cheetah", "Jaguar", "Panther", "Tiger", "Leopard", "Snow Leopard", "Lion", "Mountain Lion", "Mavericks", "Yosemite", "El Capitan", "Sierra", "High Sierra", "Mojave"};
	char *out = NULL;
	asprintf(&out, "%s 10.%hhu %s", (ver < 8)?"Mac OS X":(ver < 12)?"OS X":"macOS", ver, code[ver]);
	return out;
}
void fs(void){
	struct statfs size;
	statfs("/", &size);
	disk_total = (size.f_bsize * size.f_blocks) / GIGA;
	disk_used = disk_total - ((size.f_bsize * size.f_bavail) / GIGA);
}
double ram_used(void){
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;
	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	double out = 0;
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
	KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats, &count)){
		out = ((int64_t)vm_stats.active_count + (int64_t)vm_stats.wire_count) * (int64_t)page_size;
	}
	return out / GIGA;
}
int64_t ram_total(void){
	int64_t total;
	size_t len = sizeof(int64_t);
	sysctlbyname("hw.memsize", &total, &len, NULL, 0);
	return total / GIGAI;
}
double uptime(void){
	struct timeval boot;
	size_t len = sizeof(boot);
	sysctlbyname("kern.boottime", &boot, &len, NULL, 0);
	return difftime(time(NULL), boot.tv_sec) / (60 * 60);
}
void pkgs(void){
	gl.gl_pathc = 0;
	if(access("/usr/local/Cellar/", F_OK) != -1)
		glob("/usr/local/Cellar/*", GLOB_NOSORT, NULL, &gl);
	if(access("/opt/local/bin/", F_OK) != -1)
		glob("/opt/local/bin/*", GLOB_NOSORT, NULL, &gl);
}
char *cpu(void){
	size_t size;
	sysctlbyname("machdep.cpu.brand_string", NULL, &size, NULL, 0);
	char *out = malloc(size);
	sysctlbyname("machdep.cpu.brand_string", out, &size, NULL, 0);
	return out;
}
int main(int argc, char *argv[]){
	uname(&uts);
	fs();
	pkgs();
	
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
	if(pref.logo)
		printf(
		"os:      %s\n"
		"kernel:  %s %s %s\n"
		"cpu:     %s\n"
		"fs:      %.4g / %.4g GiB\n"
		"mem:     %.4g / %lld GiB\n"
		"uptime:  %.4g hours\n"
		"pkgs:    %zu\n"
		"shell:   %s\n"
		, ver(), uts.machine, uts.sysname, uts.release, cpu(), disk_used, disk_total, ram_used(), ram_total(), uptime(), gl.gl_pathc, basename(getenv("SHELL")));
	else
		printf(
			G"      (/        "E"os:      %s\n"
			G" ,adAb  dAba.   "E"kernel:  %s %s %s\n"
			O"d$$$$$$$$$$$$P  "E"cpu:     %s\n"
			D"$$$$$$$$$$$P    "E"fs:      %.4g / %.4g GiB\n"
			R"$$$$$$$$$$$b    "E"mem:     %.4g / %lld GiB\n"
			M"V$$$$$$$$$$$$P  "E"uptime:  %.4g hours\n"
			F" Y$$$$$$$$$$P   "E"pkgs:    %zu\n"
			F"  \"*\"~  ~\"*\"    "E"shell:   %s\n"
		, ver(), uts.machine, uts.sysname, uts.release, cpu(), disk_used, disk_total, ram_used(), ram_total(), uptime(), gl.gl_pathc, basename(getenv("SHELL")));
	return 0;
}

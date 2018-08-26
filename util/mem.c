#define GIGA (1024 * 1024 * 1024)
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>
#include <stdio.h>
double used(void){
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
int64_t total(void){
	int64_t total;
	size_t len = sizeof(int64_t);
	sysctlbyname("hw.memsize", &total, &len, NULL, 0);
	return total / GIGA;
}
char *mem(void){
	char *out;
	asprintf(&out, "%.4g / %lld GiB", used(), total());
	return out;
}
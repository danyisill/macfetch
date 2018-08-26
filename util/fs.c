#define GIGA (1024.0 * 1024 * 1024)
#include <stdio.h>
#include <sys/mount.h>
void fs(void){
	double total, used;
	struct statfs size;
	statfs("/", &size);
	total = (size.f_bsize * size.f_blocks) / GIGA;
	used = total - ((size.f_bsize * size.f_bavail) / GIGA);
	printf("disk:   %.4g / %.4g GiB\n", used, total);
}
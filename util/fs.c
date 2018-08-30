#define GIGA (1024.0 * 1024 * 1024)
#include <stdio.h>
#include <sys/mount.h>
char *fs(void){
	double total, used;
	struct statfs size;
	statfs("/", &size);
	total = (size.f_bsize * size.f_blocks) / GIGA;
	used = total - ((size.f_bsize * size.f_bavail) / GIGA);
	char *out;
	asprintf(&out, "%.4g / %.4g GiB", used, total);
	return out;
}
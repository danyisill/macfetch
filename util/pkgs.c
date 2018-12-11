#include <stdio.h>
#include <glob.h>
#include <unistd.h>

char *pkgs(void){
	glob_t gl;
	size_t total = 0;
	char *p[] = {"/usr/local/Cellar/*", "/usr/local/Caskroom/*"};
	for(int i = 0; i < (sizeof p / sizeof *p); ++i){
		glob(p[i], GLOB_NOSORT, NULL, &gl);
		total += gl.gl_pathc;
	}
	char *out;
	asprintf(&out, "%zu", total);
	return out;
}
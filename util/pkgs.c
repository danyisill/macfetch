#include <stdio.h>
#include <glob.h>
#include <unistd.h>

char *pkgs(void){
	glob_t gl;
	size_t total = 0;
	char *p[2][2] = {{"/usr/local/Cellar", "/usr/local/Cellar/*"}, {"/usr/local/Caskroom", "/usr/local/Caskroom/*"}};
	for(int i = 0; i < 2; ++i)
		if(access(p[i][0], F_OK) != -1){
			glob(p[i][1], GLOB_NOSORT, NULL, &gl);
			total += gl.gl_pathc;
		}
	char *out;
	asprintf(&out, "%zu", total);
	return out;
}
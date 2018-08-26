#include <stdio.h>
#include <glob.h>
#include <unistd.h>

char *pkgs(void){
	glob_t gl;
	char *out;
	gl.gl_pathc = 0;
	if(access("/usr/local/Cellar/", F_OK) != -1)
		glob("/usr/local/Cellar/*", GLOB_NOSORT, NULL, &gl);
	if(access("/opt/local/bin/", F_OK) != -1)
		glob("/opt/local/bin/*", GLOB_NOSORT, NULL, &gl);
	asprintf(&out, "%zu", gl.gl_pathc);
	return out;
}
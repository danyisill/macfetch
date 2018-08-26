#include <stdio.h>
#include <glob.h>
#include <unistd.h>

void pkgs(void){
	glob_t gl;
	gl.gl_pathc = 0;
	if(access("/usr/local/Cellar/", F_OK) != -1)
		glob("/usr/local/Cellar/*", GLOB_NOSORT, NULL, &gl);
	if(access("/opt/local/bin/", F_OK) != -1)
		glob("/opt/local/bin/*", GLOB_NOSORT, NULL, &gl);
	printf("pkgs:   %zu\n", gl.gl_pathc);
}
macfetch: macfetch.c
	clang -lObjC -framework Foundation -framework IOKit -o macfetch macfetch.c util/*.c util/plists.m
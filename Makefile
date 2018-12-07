macfetch: macfetch.c
	clang -lObjC -framework Foundation -o macfetch macfetch.c util/*.c util/plists.m
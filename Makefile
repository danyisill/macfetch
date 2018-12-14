macfetch: macfetch.c
	clang -framework Foundation -framework IOKit -o macfetch macfetch.c util/*.c
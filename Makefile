macfetch: macfetch.c
	clang -framework CoreFoundation -framework IOKit -o macfetch macfetch.c util/*.c
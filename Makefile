macfetch: macfetch.c
	clang -Ofast -framework CoreFoundation -framework IOKit -o macfetch macfetch.c util/*.c
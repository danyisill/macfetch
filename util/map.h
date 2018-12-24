#include <stdbool.h>
typedef struct Map {
	struct ver {
		unsigned maj;
		unsigned min;
		unsigned fix;
		char *build_ver;
	} ver;
	struct model {
		bool is_hackintosh;
		char *id;
	} model;
} Map;
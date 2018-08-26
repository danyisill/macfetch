#define GIGA (1024.0 * 1024 * 1024)
#define GIGAI (1024 * 1024 * 1024)
#define NVARS 9

#define E "\e[0m"
#define B "\e[1m"
#define G B "\e[38;5;2m"
#define O B "\e[38;5;214m"
#define D B "\e[38;5;208m"
#define R B "\e[38;5;196m"
#define M B "\e[38;5;127m"
#define F B "\e[38;5;33m"
char *apple[NVARS] = {
	G"      (/        "E,
	G" ,adAb  dAba.   "E,
	O"d$$$$$$$$$$$$P  "E,
	D"$$$$$$$$$$$P    "E,
	R"$$$$$$$$$$$b    "E,
	M"V$$$$$$$$$$$$P  "E,
	F" Y$$$$$$$$$$P   "E,
F"  \"*\"~  ~\"*\"    "E,
	"                "
};
void ver(void);
void kernel(void);
void model(void);
void cpu(void);
void fs(void);
void mem(void);
void uptime(void);
void pkgs(void);
void shell(void);
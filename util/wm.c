#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>

int main() {
    int mib[4];
    size_t len = 0;
    struct kinfo_proc *procs = NULL;
    int numProcs = 0;
    int i;
    
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;
    mib[3] = 0;
    sysctl(mib, 4, NULL, &len, NULL, 0);
    
    procs = (struct kinfo_proc *)malloc(len);
    sysctl(mib, 4, procs, &len, NULL, 0);
    
    numProcs = len / sizeof(struct kinfo_proc);
    
    for (i = 0; i < numProcs; i++) {
        if (strcmp(procs[i].kp_proc.p_comm, "Rectangle") == 0) {
            return ("Rectangle is running\n");
        } else if (strcmp(procs[i].kp_proc.p_comm, "Amethyst") == 0) {
            printf("Amethyst is running\n");
        } else if (strcmp(procs[i].kp_proc.p_comm, "BetterSnapTool") == 0) {
            printf("BetterSnapTool is running\n");
        }
    }
    
    free(procs);
    
    return 0;
}
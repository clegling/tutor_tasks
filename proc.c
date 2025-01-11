#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int pid;
    
    pid = getpid();
    if (fork() == 0) {
        printf ("%d %d\n", pid, getpid());
        exit(0);
    }

    if (fork() == 0) {
        printf ("%d\n", getppid());
        exit(0);
    }
    return 0;
}


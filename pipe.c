#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pipe(fd);

    char x[] = "123\n";

    if(fork()) {
        write(fd[1], x + 2, 1); //3
        puts(x + 1); //23\n
        wait(NULL);
    } else {
        write(fd[1], &x[0], 1); //1
        read(fd[0], x, 1);
        read(fd[0], x + 1, 1);
    }
    
    puts(x);
    return 0;
}


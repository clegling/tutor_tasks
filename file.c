#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    char buf[5] = "abcf";
    
    int fd = creat("./file.txt", 0777);
    write(fd, buf, 4);
    close(fd);

    fd = open("./file.txt", O_RDONLY);
    fork();
    read(fd, buf, 2);
    printf("%c", buf[1]);
    exit(0);
}

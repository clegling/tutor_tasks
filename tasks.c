#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int is_free(unsigned char *BitBlocks, unsigned Num, unsigned Max_Num) {
    if (Num > Max_Num) {
        return -1;
    } else {

    return (BitBlocks[Num >> 3] >> (7 - (Num & 7u))) & 1; 
    }
}


//“1.txt” – строка «abcde».
int task_1()
{
    char c = 'a';
    int fd;
    fd = open("1.txt", O_RDONLY);
    if(fork())
    {
        int fd2 = open("1.txt", O_RDONLY);
        int fd3 = dup(fd);
        lseek(fd, 2, SEEK_CUR);
        wait(NULL);
        read(fd2, &c, 1);  // a
        write(1, &c, 1);  // a
        read(fd3, &c, 1);  //d
        write(1, &c, 1);
    }
    else
    { 
        read(fd, &c, 1);  // a || c
        write(1, &c, 1); 
    }
    return 0;
}

//“1.txt” – строка «HelloWorld»
int task_2()
{
    char c = 'a';
    int fd;
    fd = open("1.txt", O_RDONLY);
    if(fork())
    {
        int fd2 = open("1.txt", O_RDONLY);
        int fd3 = dup(fd);
        lseek(fd, 5, SEEK_CUR);
        wait(NULL);
        read(fd, &c, 1); write(1, &c, 1);
        read(fd2, &c, 1); write(1, &c, 1);
        read(fd3, &c, 1); write(1, &c, 1);
    }
    else
    {
        read(fd, &c, 1); write(1, &c, 1);
    }
    return 0;
}


int task_3(int argc, char **argv)
{
    int fd[2], buf = 10;
    pipe(fd);
    // Ребёнок
    if(!fork()) {
        write (fd[1], &buf, sizeof(int));  // 10
        buf++;
        printf("%d\n", buf); // 11
    } else {
        // Родитель
        while(read(fd[0], &buf, sizeof(int))) {
            buf--; //9
            printf("%d\n", buf); // 9
        }
    }
    return 0;
}

//“1.txt” – строка «examos». 
int task_4()
{
    char c = 'a';
    int fd;
    fd = open("1.txt", O_RDONLY);
    if(fork())
    {
        int fd2 = open("1.txt", O_RDONLY);
        int fd3 = dup(fd);
        lseek(fd, 2, SEEK_CUR);
        wait(NULL);
        read(fd2, &c, 1); write(1, &c, 1);
        read(fd3, &c, 1); write(1, &c, 1);
    }
    else
    { read(fd, &c, 1); write(1, &c, 1); }
    return 0;
}

int task_5(int argc, char **argv)
{
    int fd[2];
    char c[2] = "ab";
    pipe(fd);
    if(!fork()) { /* процесс №2 */
        close (fd[1]);
        read(fd[0], c, 1);
        _exit(0);
    }
    /* процесс №1 */
    close (fd[0]);
    wait(NULL);
    exit(0);
}

int task_6(int argc, char **argv)
{
    int fd[2];
    char c[2] = "ab";
    pipe(fd);
    close (fd[1]);
    if(fork()) {/*процесс №1*/
        close (fd[0]);
        wait(NULL);
    } else {/*процесс №2*/
        read(fd[0],c,1);
    }
}

int task_7()
{
    int fd[2];
    char c[2]="34";
    pipe(fd);
    write(fd[1], c, 2); // 34
    if(fork())
        fork();
    read(fd[0], c, 1); // 3 процесса  // 3  // 4 // ждет
    putchar('3'); // 334434 343434
    putchar('4'); // 343344   334344
    write(fd[1], c, 1);
    wait(NULL);
    return 0;
}

int main()
{
    return 0;
}

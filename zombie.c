#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
 
int main ()
{
    pid_t child_pid;

    child_pid = fork ();
    if (child_pid > 0) {
        sleep (60);
    } else {
        exit (0);
    }
    // Результат: зомби-процесс на время, пока спит родитель
    return 0;
}

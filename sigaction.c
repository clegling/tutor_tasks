#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int count = 1;

struct sigaction action, sa;

void SigHandler(int s)
{
    printf("\nI got SIGINT %d time(s)\n", count++);
    if (count == 5)
    {
        /*изменяем указатель на функцию-обработчик сигнала*/
        action.sa_handler = SIG_DFL;
        /* изменяем обработчик для сигнала SIGINT */
        sigaction(SIGINT, &action, &sa);
    }
}

int main(int argc, char **argv)
{
    sigset_t sigset;
    
    // инициализируем набор сигналов
    sigemptyset(&sigset); 
    
    // добавляем в набор сигналов бит, соответствующий сигналу SIGIN
    sigaddset(&sigset, SIGINT); 

    // устанавливаем новую сигнальную маску
    if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1)
    {
        printf("sigprocmask() error\n");
        return -1;
    }
    
    // инициализируем указатель на функцию-обработчик сигнала
    action.sa_handler = SigHandler;

    // изменяем обработчик по умолчанию для сигнала SIGINT
    sigaction(SIGINT, &action, &sa);
    while(1);
    return 0;
}

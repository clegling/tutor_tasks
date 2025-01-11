#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define ALARM_TIMER 1


void alrm(int s) {
    printf("\nжду ввода:\n");
    //printf("Проснулся\n");
}


int main(int argc, char **argv) {
    char s[80];
    int pid;

    // Установка обработчика alrm на приход сигнала SIGALRM
    signal(SIGALRM, alrm);

    if ((pid = fork()))
    {
        // Родительский процесс
        for (;;) {
            sleep(ALARM_TIMER);
            //Отправка сигнала
            kill(pid, SIGALRM);
        }
    }
    else {
        // Дочерний процесс
        printf("Введите имя:");
        gets(s);
        printf("Спасибо, %s!\n", s);
        //Отправка сигнала
        kill(getppid(), SIGKILL);
    }
    
    return 0;
}

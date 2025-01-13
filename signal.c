#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int count = 0;

// функция – пользовательский обработчик сигнала
void SigHndlr (int s)
{
    printf("\n I got SIGINT %d time(s) \n",++ count);
    if (count == 5) {
        // ставим  обработчик сигнала по умолчанию 
        signal (SIGINT, SIG_DFL);
    } else {
        // восстанавливаем  обработчик сигнала
        signal (SIGINT, SigHndlr); 
    }
}

int main(int argc, char **argv)
{
    // установка реакции на сигнал 
    signal (SIGINT, SigHndlr);
    while (1);
    return 0;
}

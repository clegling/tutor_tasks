#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    struct
    {
        long mestype;
        char mes[100];
    } messageto;
    
    struct
    {
        long mestype;
        long mes;
    } messagefrom;

    key_t key;
    int mesid;
    key = ftok("example", 'r');
    mesid = msgget (key, 0666 | IPC_CREAT | IPC_EXCL );

    while(1)
    {
        msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), 1, 0);
        messageto.mestype = messagefrom.mes;
        strcpy(messageto.mes, "Message for client");
        msgsnd (mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
    }
}
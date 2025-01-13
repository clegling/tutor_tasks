#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORTNUM 50500
#define BUFLEN 80
#define QUESIZE 5 /* условный размер очереди запросов на соединение */


int main(int argc, char **argv)
{
    struct sockaddr_in own_addr, party_addr;
    int sockfd, newsockfd;
    int party_len, len;
    
    char buf[BUFLEN];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&own_addr, 0, sizeof(own_addr));

    own_addr.sin_family = AF_INET;
    own_addr.sin_addr.s_addr = INADDR_ANY; 
    own_addr.sin_port = htons(PORTNUM);
    
    // связываем основной сокет, используем приведение типа между указателями на фактическую и формальную структуры данных 
    bind(sockfd, (struct sockaddr *) &own_addr, sizeof(own_addr));

    // Разрешаем обработку запросов на соединение, QUESIZE - условный размер очереди запросов
    listen(sockfd, QUESIZE);
    
    while (1) {
   
        memset(&party_addr, 0, sizeof(party_addr));
        party_len = sizeof(party_addr);
        
        //создание соединения – при подключении нового клиента система заполняет party_addr информацией о клиенте (IP адрес, порт)*/
        newsockfd = accept(sockfd, (struct sockaddr *)&party_addr, &party_len);
        
        //обрабатываем соединение нового клиента в отдельном процессе*
        if (!fork()) {
            
            // сын - обрабатывает запрос и посылает ответ
            close(sockfd); // этот сокет сыну не нужен

            len = recv(newsockfd, &buf, BUFLEN, 0);

            char str[40];
            inet_ntop(AF_INET, &party_addr, str, sizeof(str));
            printf("received string %s from client %s:%d \n", buf, str, ntohs(party_addr.sin_port));

            sprintf(buf, "%d", strlen(buf));
            send(newsockfd, buf, strlen(buf) + 1, 0);

            close(newsockfd);
            return 0;
        }
        /*отец-закрывает новый сокет, продолжает прослушивать старый*/
        close(newsockfd);
    }
}
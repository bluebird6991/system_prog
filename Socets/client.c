#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
 
int main (int argc, char **argv)
{
char message[2048];//=(char*)malloc(sizeof(char));// сообщение на передачу
char buf[sizeof(message)];
int port,ch;
//----------------------------------------------------------------------------
if(argc!=3){
printf("Не верное кол-во аргументов!\nДолжно быть 2 аргумента (Порт,ip-адрес -сервера)!\n");
exit(0);
}
 
    int sock;                 // дескриптор сокета
    struct sockaddr_in addr; // структура с адресом
    struct hostent* hostinfo;
port = atoi(argv[1]);
hostinfo = argv[2];
    sock = socket(AF_INET, SOCK_STREAM, 0); // создание TCP-сокета
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
 
    // Указываем параметры сервера
    addr.sin_family = AF_INET; // домены Internet
    addr.sin_port = htons(port); // или любой другой порт...
    addr.sin_addr.s_addr=inet_addr(hostinfo);
    /*
     * Начинающие программисты часто спрашивают, как можно отлаживать сетевую программу, если под рукой нет сети.
     * Оказывается, можно обойтись и без неё. Достаточно запустить клиента и сервера на одной машине, а затем использовать для соединения адрес интерфейса внутренней петли (loopback interface).
     * В программе ему соответствует константа INADDR_LOOPBACK (не забудьте применять к ней функцию htonl!).
     * Пакеты, направляемые по этому адресу, в сеть не попадают.
     * Вместо этого они передаются стеку протоколов TCP/IP как только что принятые.
     * Таким образом моделируется наличие виртуальной сети, в которой вы можете отлаживать ваши сетевые приложения.
     */
   // addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
      //addr.sin_addr.s_addr = inet_addr(host_ip);
 if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) // установка соединения с сервером
    {
        perror("Подключение");
        exit(2);
    }
 
while(1){//WHILE <---
//----------------------------------------------------------------------------
    printf("Введите сообщение серверу(Для выхода:exit): "); 
    if (!strcmp(gets(message), "exit")){close(sock);return 0;}
//----------------------------------------------------------------------------
 
    printf("отправка сообщения на сервер...\n");
    send(sock, message, sizeof(message), 0); // отправка сообщения на сервер
    int bytes_read = 0;
    printf("Ожидание сообщения\n");
    bytes_read = recv(sock, buf, sizeof(message), 0);
    printf("Получено %d bytes\tСообщение: %s\n", bytes_read, buf); // прием сообщения от сервера
    
 
}//END_WHILE
    
return 0;
    
}
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    int sock, listener;       // дескрипторы сокетов
    struct sockaddr_in addr; // структура с адресом
    char buf[2048];       // буфур для приема
    int bytes_read;           // кол-во принятых байт
 
 
    listener = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет для входных подключений
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    // Указываем параметры сервера
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) // связываемся с сетевым устройство. Сейчас это устройство lo - "петля", которое используется для отладки сетевых приложений
    {
        perror("bind");
        exit(2);
    }
 
    listen(listener, 1); // очередь входных подключений
    
    while(1)
    {
        sock = accept(listener, NULL, NULL); // принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
        if(sock < 0)
        {
            perror("Прием входящих подключений");
            exit(3);
        }
 
switch(fork())
{
case -1:
 perror("fork");
 break;
case 0:
close(listener);
 
 
        while(1)
        {
            printf("Ожидаем сообщение...\n");
 
 
            bytes_read = recv(sock, buf, 2048, 0); // принимаем сообщение от клиента
            if(bytes_read <= 0) break;
            printf("Получено %d bytes\tСообщение: %s\n", bytes_read, buf);
            printf("Отправляю принятое сообщение клиенту\n");
            send(sock, buf, bytes_read, 0); // отправляем принятое сообщение клиенту
        }
    
        close(sock); // закрываем сокет
        _exit(0);
default:
close(sock);
}   
    }
    
    return 0;
}
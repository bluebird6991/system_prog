/*
 *  ioctl.c - Пример программы, использующей ioctl для управления модулем ядра
 *
 *  До сих пор мы ползовались командой cat, для передачи данных в/из модуля.
 *  Теперь же мы должны написать свою программу, которая использовала бы ioctl.
 */

/* 
 * Определения старшего номера устройства и коды операций ioctl
 */
#include "chardev.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      /* open */
#include <unistd.h>     /* exit */
#include <sys/ioctl.h>  /* ioctl */

/* 
 * Функции работы с драйвером через ioctl  
 */

void ioctl_set_msg(int file_desc, char *message){
    int ret_val;

    ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);

    if (ret_val < 0) {
        printf("Ошибка при вызове ioctl_set_msg: %d\n", ret_val);
        exit(-1);
    }
}

void ioctl_get_msg(int file_desc){
    int ret_val;
    char message[100];

  /* 
   * Внимание - ядро понятия не имеет -- какой длины буфер мы используем
   * поэтому возможна ошибка, связанная с переполнением буфера.
   * В реальных проектах вам необходимо предусмотреть
   * передачу в ioctl двух дополнительных параметров:
   * собственно буфера сообщения и его длину
   */
    ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

    if (ret_val < 0) {
        printf("Ошибка при вызове ioctl_get_msg: %d\n", ret_val);
        exit(-1);
    }

    printf("Получено сообщение (get_msg): %s\n", message);
}

void ioctl_get_nth_byte(int file_desc){
    int i;
    char c;

    printf("N-ный байт в сообщении (get_nth_byte): ");

    i = 0;
    while (c != 0){
        c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, i++);

        if (c < 0){
            printf("Ошибка при вызове ioctl_get_nth_byte на %d-м байте.\n", i);
            exit(-1);
        }
        putchar(c);
    }
    putchar('\n');
}

/* 
 * Main - Проверка работоспособности функции ioctl
 */
void main(){
    int file_desc, ret_val;
    char *msg = "Это сообщение передается через ioctl\n";
    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Невозможно открыть файл устройства: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    ioctl_get_nth_byte(file_desc);
    ioctl_get_msg(file_desc);
    ioctl_set_msg(file_desc, msg);

    close(file_desc);
}
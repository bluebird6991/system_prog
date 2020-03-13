/*
 *  chardev.c - Пример создания символьного устройства 
 *              доступного на запись/чтение
 */

#include <linux/module.h> /* Необходимо для любого модуля */
#include <linux/kernel.h> /* Все-таки мы работаем с ядром! */
#include <linux/fs.h>
#include <asm/uaccess.h>        /* определения функций get_user и put_user */

#include "chardev.h"
#define SUCCESS 0
#define DEVICE_NAME "char_dev"
#define BUF_LEN 80

/* 
 * Устройство уже открыто? Используется для
 * предотвращения конкурирующих запросов к устройству
 */
static int Device_Open = 0;

/* 
 * Ответ устройства на запрос
 */
static char Message[BUF_LEN];

/* 
 * Позиция в буфере.
 * Используется в том случае, если сообщение оказывется длиннее
 * чем размер буфера. 
 */
static char *Message_Ptr;

/* 
 * Вызывается когда процесс пытается открыть файл устройства
 */
static int device_open(struct inode *inode, struct file *file){
#ifdef DEBUG
    printk("device_open(%p)\n", file);
#endif

  /* 
   * В каждый конкретный момент времени только один процесс может открыть файл устройства 
   */
    if (Device_Open)
        return -EBUSY;

    Device_Open++;
  /*
   * Инициализация сообщения
   */
    Message_Ptr = Message;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file){
#ifdef DEBUG
    printk("device_release(%p,%p)\n", inode, file);
#endif

  /* 
   * Теперь мы готовы принять запрос от другого процесса
   */
    Device_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}

/* 
 * Вызывается когда процесс, открывший файл устройства
 * пытается считать из него данные.
 */
static ssize_t device_read(struct file *file, /* см. include/linux/fs.h   */
            char __user * buffer,             /* буфер для сообщения */
            size_t length,                    /* размер буфера       */
            loff_t * offset){
  /* 
   * Количество байт, фактически записанных в буфер
   */
    int bytes_read = 0;

#ifdef DEBUG
    printk("device_read(%p,%p,%d)\n", file, buffer, length);
#endif

  /* 
   * Если достигнут конец сообщения -- вернуть 0
   * (признак конца файла) 
   */
    if (*Message_Ptr == 0)
        return 0;

  /* 
   * Собственно запись данных в буфер
   */
    while (length && *Message_Ptr) {

    /* 
     * Поскольку буфер располагается в пространстве пользователя,
     * обычное присвоение не сработает. Поэтому
     * для записи данных используется put_user,
     * которая копирует данные из пространства ядра
     * в пространство пользователя.
     */
        put_user(*(Message_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

#ifdef DEBUG
    printk("Read %d bytes, %d left\n", bytes_read, length);
#endif

  /* 
   * Вернуть количество байт, помещенных в буфер.
   */
    return bytes_read;
}

/* 
 * Вызывается при попытке записи в файл устройства
 */
static ssize_t device_write(struct file *file,
                            const char __user * buffer,
                            size_t length,
                            loff_t * offset){
    int i;

#ifdef DEBUG
    printk("device_write(%p,%s,%d)", file, buffer, length);
#endif

    for (i = 0; i < length && i < BUF_LEN; i++)
        get_user(Message[i], buffer + i);

    Message_Ptr = Message;

  /* 
   * Вернуть количество принятых байт
   */
    return i;
}

/* 
 * Вызывается, когда процесс пытается выполнить операцию ioctl над файлом устройства.
 * Кроме inode и структуры file функция получает два дополнительных параметра:
 * номер ioctl и дополнительные аргументы.
 *
 */
int device_ioctl(struct inode *inode, /* см. include/linux/fs.h */
      struct file *file,              /* то же самое */
      unsigned int ioctl_num,         /* номер и аргументы ioctl */
      unsigned long ioctl_param){
    int i;
    char *temp;
    char ch;

  /* 
   * Реакция на различные команды ioctl 
   */
    switch (ioctl_num){
        case IOCTL_SET_MSG:
    /* 
     * Принять указатель на сообщение (в пространстве пользователя) 
     * и переписать в буфер. Адрес которого задан в дополнительно аргументе.
     */
        temp = (char *)ioctl_param;

    /* 
     * Найти длину сообщения
     */
        get_user(ch, temp);
        
        for (i = 0; ch && i < BUF_LEN; i++, temp++)
            get_user(ch, temp);

        device_write(file, (char *)ioctl_param, i, 0);
        break;

    case IOCTL_GET_MSG:
    /* 
     * Передать текущее сообщение вызывающему процессу - 
     * записать по указанному адресу.
     */
        i = device_read(file, (char *)ioctl_param, 99, 0);

    /* 
     * Вставить в буфер завершающий символ \0
     */
        put_user('\0', (char *)ioctl_param + i);
        break;

    case IOCTL_GET_NTH_BYTE:
    /* 
     * Этот вызов является вводом (ioctl_param) и 
     * выводом (возвращаемое значение функции) одновременно
     */
        return Message[ioctl_param];
        break;
    }

    return SUCCESS;
}

/* Объявлнеия */

/* 
 * В этой структуре хранятся адреса функций-обработчиков
 * операций, производимых процессом над устройством.
 * Поскольку указатель на эту структуру хранится в таблице устройств,
 * она не может быть локальной для init_module. 
 * Отсутствующие указатели в структуре забиваются значением NULL.
 */
struct file_operations Fops = {
    .read = device_read,
    .write = device_write,
    .ioctl = device_ioctl,
    .open = device_open,
    .release = device_release,    /* оно же close */
};

/* 
 * Инициализация модуля - Регистрация символьного устройства
 */
int init_module(){
    int ret_val;
  /* 
   * Регистрация символьного устройства (по крайней мере - попытка регистрации) 
   */
    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

  /* 
   * Отрицательное значение означает ошибку
   */
    if (ret_val < 0) {
        printk("%s failed with %d\n", "Sorry, registering the character device ", ret_val);
        return ret_val;
    }

    printk("%s The major device number is %d.\n", "Registeration is a success", MAJOR_NUM);
    printk("If you want to talk to the device driver,\n");
    printk("you'll have to create a device file. \n");
    printk("We suggest you use:\n");
    printk("mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
    printk("The device file name is important, because\n");
    printk("the ioctl program assumes that's the\n");
    printk("file you'll use.\n");

    return 0;
}

/* 
 * Завершение работы модуля - дерегистрация файла в /proc 
 */
void cleanup_module(){
    int ret;

  /* 
   * Дерегистрация устройства
   */
    ret = unregister_chrdev(MAJOR_NUM, DEVICE_NAME);

  /* 
   * Если обнаружена ошибка -- вывести сообщение
   */
    if (ret < 0)
        printk("Error in module_unregister_chrdev: %d\n", ret);
}
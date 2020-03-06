/*
 *  procfs.c -  пример создания "файла" в /proc
 */

#include <linux/module.h> /* Необходимо для любого модуля */
#include <linux/kernel.h> /* Все-таки мы работаем с ядром! */
#include <linux/proc_fs.h>/* Необходимо для работы с файловой системой /proc */

struct proc_dir_entry *Our_Proc_File;

/* Обработчик чтения из файла в /proc.
 * 
 * Аргументы
 * =========
 * 1. Буфер с данными. Как его заполнить -- вы решаете сами
 * 2. Указатель на указатель на строку символов. 
 *    Если вы не желаете использовать буфер
 *    размещенный ядром.
 * 3. Текущая позиция в файле
 * 4. Размер буфера.
 * 5. Признак конца файла, "1" == EOF.
 * 6. Указатель на данные (необходим в случае единственного
 *    обработчика на несколько файлов в /proc)
 *
 * Порядок использования и возвращаемое значение
 * =============================================
 * Нулевое значение == "буфер пуст", т.е. "Конец файла". 
 * Отрицательное значение == код ошибки.
 *
 * Дополнительные сведения
 * =======================
 * Основные принципы реализации этой функции
 * я почерпнул не из документации, а из исходных текстов
 * модулей, выполняющих подобные действия. Меня интересовало использование
 * поля get_info в структуре proc_dir_entry (Если вам это интересно
 * то для поиска я пользовался утилитами find и grep),
 * Интересующий меня пример я нашел в <kernel source
 * directory>/fs/proc/array.c.
 *
 * Когда вам что-то непонятно, то лучше всего
 * поискать примеры в исходных текстах ядра. В этом состоит
 * огромное преимущество Linux перед другими ОС,
 * так как нам доступны все исходные тексты, так что -- 
 * пользуйтесь этим преимуществом!
 */
ssize_t
procfile_read(char *buffer,
              char **buffer_location,
              off_t offset, int buffer_length, int *eof, void *data)
{
  printk(KERN_INFO "inside /proc/test : procfile_read\n");

  int len = 0;          /* Фактическое число байт */
  static int count = 1;

  /* 
   * Мы всегда должны выдавать имеющуюся информацию,
   * если пользователь спрашивает -- мы должны ответить.
   *
   * Это очень важно, поскольку библиотечная функция read
   * будет продолжать обращаться к системному вызову
   * read до тех пор, пока ядро не ответит, что сведений больше нет
   * или пока буфер не будет заполнен.
   */
  if (offset > 0) {
    printk(KERN_INFO "offset %d : /proc/test : procfile_read, \
           wrote %d Bytes\n", (int)(offset), len);
    *eof = 1;
    return len;
  }

  /* 
   * Заполнить буфер и получить его размер
   */
  len = sprintf(buffer,
          "For the %d%s time, go away!\n", count,
          (count % 100 > 10 && count % 100 < 14) ? "th" :
          (count % 10 == 1) ? "st" :
          (count % 10 == 2) ? "nd" :
          (count % 10 == 3) ? "rd" : "th");
  count++;

 /* 
  * Вернуть размер буфера
  */
  printk(KERN_INFO
         "leaving /proc/test : procfile_read, wrote %d Bytes\n", len);
  return len;
}

int init_module()
{
  int rv = 0;
  printk(KERN_INFO "Trying to create /proc/test:\n");

  Our_Proc_File = create_proc_entry("test", 0644, NULL);

  if (Our_Proc_File == NULL) {
    rv = -ENOMEM;
    remove_proc_entry("test", &proc_root);
    printk(KERN_INFO "Error: Could not initialize /proc/test\n");
  } else {
    printk(KERN_INFO "Success!\n");
  }

  Our_Proc_File->read_proc = procfile_read;
  Our_Proc_File->owner = THIS_MODULE;
  Our_Proc_File->mode = S_IFREG | S_IRUGO;
  Our_Proc_File->uid = 0;
  Our_Proc_File->gid = 0;
  Our_Proc_File->size = 37;

  return rv;
}

void cleanup_module()
{
  remove_proc_entry("test", &proc_root);
  printk(KERN_INFO "/proc/test removed\n");
}
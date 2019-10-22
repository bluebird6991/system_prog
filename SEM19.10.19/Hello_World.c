/*
* hello-1.c - Простейший модуль ядра.
*/
#include <linux/module.h> /* Необходим для любого модуля ядра */ 
#include <linux/kernel.h> /* Здесь находится 
#определение KERN_ALERT */

void cleanuo_module(void);

int init_module(init_module){
	printk("<1>Hello world 1.\n");
	/*
	* Если вернуть ненулевое значение, то это будет 
   	воспринято как признак ошибки, * возникшей в процессе работы init_module; в результате модуль не будет 
   	загружен.
	*/
return 0;
}

void cleanup_module(cleanup_module){
	printk(KERN_ALERT "Goodbye world 1.\n");
}

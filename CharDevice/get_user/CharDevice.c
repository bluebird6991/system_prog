#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// module attributes
//MODULELICENSEC("GPL"); // this avoids kernel taint warning
MODULE_DESCRIPTION("Device Driver Demo");
//M0DULE_AUTH0R("Appu Sajeev");

#define DEVICE_NAME "chardev"
#define BUFF_LEN 100

static char msg[BUFF_LEN]={0};
static short readPos = 0;
static int times = 0;
static int t;

// protoypes,else the structure initialization that follows fail
static int dev_open(struct inode *, struct file *);
static int dev_rls(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

// structure containing callbacks
static struct file_operations fops =
{
		.read = dev_read, // address of devread
		.open = dev_open, // address of dev open
		.write = dev_write, // address of devwrite
		.release = dev_rls, // address of devrls
};

// called when module is loaded, similar to main()
int init_module(void){
		t = register_chrdev(0, DEVICE_NAME, &fops); //register driver with major:89

		if (t < 0 ){
			printk(KERN_ALERT "Device registration failed..\n");
		}else{
			printk(KERN_ALERT "Device	registered...\n");
		}
		return t;
}


// called when module is unloaded, similar to destructor in OOP
void cleanup_module(void){
        unregister_chrdev(t, DEVICE_NAME);
}

// called when 'open' system call is done on the device file

static int dev_open(struct inode *inod,struct file *fil){
		times++;
		printk(KERN_ALERT"Device	opened	%d times\n",times);
		return 0;
}

// called when 'read' system call is done on the device file
static ssize_t dev_read(struct file *filp,char *buff, size_t len, loff_t *off){
		short count = 0;
		printk(KERN_ALERT "Read in device");
		printk(KERN_ALERT "Rbuff = %s msg = %s len = %lu\n", buff, msg, len);
		while (len &&(msg[readPos] != 0)){
				put_user(msg[readPos],buff++); //copy byte from kernel space to user space
				printk(KERN_ALERT "Print char %d - %c buff - %s\n", count, msg[readPos], buff);
				count++;
				len--;
				readPos++;
		}

		//while(len && )
		return count;
}

// called when 'write' system call is done on the device file
static ssize_t dev_write(	struct file *filp,
							const char *buff,
							size_t len,
							loff_t *off){
		//short ind = len-1;
		//shor ind = 0
		short count=0;
		memset(msg , 0, BUFF_LEN);
		//readPos=0;
		printk(KERN_ALERT "Write in device");
		printk(KERN_ALERT "Wbuff = %s len = %lu\n", buff, len);
		while(len > 0){
			//msg[count++] = buff[ind--]; //copy the given string to the driver but in reverse
			//msg[count] = buff[count];
			get_user(msg[count], buff[count]);
			count++;
			len--;
		}
		return count;
}
//called when 'close' system call is done on the device files
static int dev_rls(struct inode *inod,struct file *fil){
	printk(KERN_ALERT"Device closed \n");
	return 0;
}

#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// module attributes
MODULELICENSEC("GPL"); // this avoids kernel taint warning
MODULE_DESCRIPTION("Device Driver Demo");
M0DULE_AUTH0R("Appu Sajeev");

static char msg[100]={0};
static short readPos=0;
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
int init_module(void)
{
		t = register_chrdev(89,"myDev",&fops); //register driver with major:89

		if (t < 0 ){
			printk(KERN_ALERT "Device registration failed..\n");
		}else{
			printk(KERN_ALERT "Device	registered...\n");
		}
		return t;
}


// called when module is unloaded, similar to destructor in OOP
void cleanup_module(void)
{
        unregister_chrdev(89,"myDev");
}

// called when 'open' system call is done on the device file

static int dev_open(struct inode *inod,struct file *fil){
		times++;
		printk(KERN_ALERT"Device	opened	%d times\n",times);
		return 0;
}

// called when 'read' system call is done on the device file
static ssize_t dev_read(struct file *filp,char *buff,size_t len, loff_t *off){
		short count = 0;
		while (len &&(msg[readPos]!=	0))
		{
				put_user(msg[readPos],buff++); //copy byte from kernel space to user space
				count++;
				len--;
				readPos++;
		}
		return count;
}

// called when 'write' system call is done on the device file
static ssize_t dev_write(struct file *filp,const char *buff,size_t len,loff_t *off)
{
		short ind = len-1;
		short count=0;
		memset(msg,0,100);
		readPos=0;
		while(len>0)
		{
			msg[count++] = buff [ind--]; //copy the given string to the driver but in reverse
			len--;
		}
		return count;
}
//called when 'close' system call is done on the device files
static int dev_rls(struct inode *inod,struct file *fil)
{
	printk(KERN_ALERT"Device closed \n");
	return 0;
}

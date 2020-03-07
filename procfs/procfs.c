#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/proc_fs.h>
/* Specifically, a module */
/* We're doing kernel work */
/* Necessary because we use the proc fs */
#define procfs_name "helloworld"
/**
 * This structure hold information about the /proc file
 *
 */
struct proc_dir_entry *Our_Proc_File;
/* Put data into the proc fs file. *
* Arguments
* =========
* 1. *
* 2. *
*
* 3.
* 4.
* 5.
* 6.
*
*
* Usage and Return Value
* ======================
* A return value of zero means you have no further
* information at this time (end of file). A negative
* return value is an error condition. *
* For More Information
* ====================
* The way I discovered what to do with this function * wasn't by reading documentation, but by reading the
* code which used it. I just looked to see what uses
* the get_info field of proc_dir_entry struct (I used a * combination of find and grep, if you're interested), * and I saw that it is used in <kernel source
* directory>/fs/proc/array.c.
*
* If something is unknown about the kernel, this is * usually the way to go. In Linux we have the great * advantage of having the kernel source code for
* free − use it.
*/
int procfile_read(  char *buffer,
                    char **buffer_location,
                    off_t offset,
                    int buffer_length,
                    int *eof,
                    void *data){
    int ret;
    printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);
/*
 * We give all of our information in one go, so if the
 * user asks us if we have more information the
 * answer should always be no.
*
* This is important because the standard read
* function from the library would continue to issue * the read system call until the kernel replies
* that it has no more information, or until its
* buffer is filled.
*/
    if (offset > 0) {
        /* we have finished to read, return 0 */ 
        ret = 0;
    } else {
        /* fill the buffer, return the buffer size */
        ret = sprintf(buffer, "HelloWorld!\n");
    }
    return ret;
}

int init_module() {
    Our_Proc_File = create_proc_entry(procfs_name, 0644, NULL);
    if (Our_Proc_File == NULL) {
        remove_proc_entry(procfs_name, &proc_root);
        printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", procfs_name); 
        return −ENOMEM;
    }
    Our_Proc_File->read_proc    = procfile_read;
    Our_Proc_File->owner        = THIS_MODULE;
    Our_Proc_File->mode         = S_IFREG | S_IRUGO;
    Our_Proc_File->uid          = 0;
    Our_Proc_File->gid          = 0;
    Our_Proc_File->size         = 37;

    printk(KERN_INFO "/proc/%s created\n", procfs_name);
    return 0; /* everything is ok */

void cleanup_module() {
    remove_proc_entry(procfs_name, &proc_root);
    printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}
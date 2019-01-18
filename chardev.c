#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int Major;
static int Device_Open = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;

struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

int init_module(void){
  Major = register_chr(0, DEVICE_NAME, &fops);

  if (Major < 0){
    printk(KERN_ALERT "Registering Device FAILED with %d \n", Major);
    return Major;
  }
  printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
  printk(KERN_INFO "the driver, create a dev file with\n");
  printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
  printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
  printk(KERN_INFO "the device file.\n");
  printk(KERN_INFO "Remove the device file and module when done.\n");

  return SUCCESS;

}

void cleanup_module(void)
{
    /* 
     *   * Unregister the device 
     *     */
    int ret = unregister_chrdev(Major, DEVICE_NAME);
      if (ret < 0)
            printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}
}



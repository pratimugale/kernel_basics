#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "pratimdevice"

//create a structure for our fake device

struct fake_device{
  char data[100];
  //struct semaphore sem;
} virtual_device;

struct cdev *mycdev;


static dev_t first;

// writing the file operations functions

int device_open(struct inode *inode, struct file *filp){
  printk(KERN_ALERT "Device was opened \n");
  return 0;

}

ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount, loff_t*curOffset){
  printk(KERN_ALERT " Reading from device \n");
  return copy_to_user(bufStoreData, virtual_device.data, bufCount);
}

ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCount, loff_t*curOffset){
  printk(KERN_ALERT " Writing to device \n");
  return copy_from_user(virtual_device.data, bufSourceData, bufCount);
}

int device_close(struct inode *inode, struct file *filp){
  printk(KERN_ALERT "Device was closed \n");
  return 0;

}


// now writing our file operations structure which tells which functions to
// call when user operates on our device file
struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = device_open,
  .release = device_close,
  .write = device_write,
  .read = device_read
};

static int __init mychar_init(void){
  printk(KERN_ALERT "Start by Registering \n");
  if(alloc_chrdev_region(&first, 0, 1, "Pratim") < 0){
    printk(KERN_ALERT "Registration FAILED \n");
    return -1;
  }
  printk(KERN_INFO "<MAJOR, MINOR> : <%d, %d> \n", MAJOR(first), MINOR(first) );
  //printk(KERN_INFO "\t use ", MAJOR(first), MINOR(first) );

  // Now creating the cdev structure
  mycdev = cdev_alloc();
  mycdev->ops = &fops;
  mycdev->owner = THIS_MODULE;

  // We created cdev, now assign it to the kernel
  // cdev_add(mycdev, dev_num, 1)

  if(cdev_add(mycdev, first, 1) < 0){
    // Always check for errors
    printk(KERN_ALERT "unable to add cdev to kernel \n");
    return -1;
  }

  return 0;
}

static void __exit mychar_exit(void){
  cdev_del(mycdev);

  unregister_chrdev_region(first, 1);
  printk(KERN_ALERT "Device Unregistered \n");
}
module_init(mychar_init);
module_exit(mychar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pratim Ugale");
MODULE_DESCRIPTION("My first character driver");


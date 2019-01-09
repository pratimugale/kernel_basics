#include <linux/init.h>
#include <linux/module.h>
//For parameters:
#include <linux/moduleparam.h>

//Create variable
int param_var = 0;
//register the variable created
//permissions: S_I is the general beginning
// S_IRUSR : R-reading
// S_IWUSR : W-writing
// S_IXUSR : X-execution
//           USR - user
// S_IWGRP : GRP - group
// S_IRGRP :
// |       : XOR for two permissions
module_param(param_var, int, S_IRUSR | S_IWUSR);

void display(void){
  printk(KERN_ALERT "Test: param = %d \n", param_var);
}

static int parameter_init(void){
  printk(KERN_ALERT "Purpose is to register functionalities and allocate resources\n");
  display();
  return 0;
}

static void parameter_exit(void){
  printk(KERN_ALERT "Module exit\n");
}

module_init(parameter_init);
module_exit(parameter_exit);

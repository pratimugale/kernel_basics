#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>

static const char state_name[] = TASK_STATE_TO_CHAR_STR;

void device_init(void){
  struct task_struct *task = current_thread_info()->task;
  printk(KERN_NOTICE "Current Process Name: %s", task->comm);
  printk(KERN_NOTICE "Current Process ID: %d", task->pid);
  printk(KERN_NOTICE "Current Process CPU: %d", task->cpu);
  printk(KERN_NOTICE "Current Process State: %c", state_name[task->state]);
}

void device_exit(void)
{
    printk(KERN_NOTICE "task_struct example exit\n");
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pratim Ugale");
MODULE_DESCRIPTION("task struct example");


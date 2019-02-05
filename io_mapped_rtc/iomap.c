#include <linux/module.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <asm/io.h>

#define RTC_INDEX     0x70
#define RTC_DATA      0x71

#define SECONDS       0x00
#define MINUTES       0x02
#define HOURS         0x04
#define DAY_WEEK      0x06
#define DAY_MONTH     0x07
#define MONTH         0x08
#define YEAR          0x09

#define REGA          0x0A
#define REGB          0x0B
#define REGC          0x0C
#define REGD          0x0D

struct time{
  u8 minute;
  u8 seconds;
  u8 hours;
  u8 day_of_week;
  u8 day_of_month;
  u8 month;
  u8 year;
};

unsigned char *day[] = {"0", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAR"};
unsigned char *month[] = {"0", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

struct time read_time(void){
  struct time t1;

  outb_p(YEAR, RTC_INDEX);
  t1.year = inb(RTC_DATA);

  return t1;
}

static int __init rtc_init(void){
  u8 temp;
  temp = inb(0x84);
  printk(KERN_ALERT "The Value at 0x84 is:  %d \n", temp);
  struct time t =  read_time();
  printk(KERN_ALERT "YEAR: %d \n",t.year);

  return 0;
}

static void __exit rtc_exit(void){
  outb(0x0d, RTC_INDEX);
}

module_init(rtc_init);
module_exit(rtc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pratim Ugale");
MODULE_DESCRIPTION("To study IO mapped hardware using an example of RTC");



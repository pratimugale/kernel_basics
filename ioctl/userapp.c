// Program to print a message in the message buffer of the kernel using IOCTL

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// IOCTL essentials:
#include <sys/ioctl.h>
#define PRINTCODE _IOW(240, 0, char*)

#define DEVICE "/dev/pratimdevice1"

int main(){
  int i, fd;
  fd = open(DEVICE, O_RDWR);

  if (fd == -1){
    printf("File does not exist");
    //exit(-1);
  }

  ioctl(fd, PRINTCODE, "Hi this is Pratim's IOCTL Code");

  char read_buf[100];
  read(fd, read_buf, sizeof(read_buf));
  printf("device says %s \n", read_buf);


  // writing to device

   /*char write_buf[100] = "Hi this is pratim";
  write(fd, write_buf, sizeof(write_buf));*/

  /*char read_buf[100];
  read(fd, read_buf, sizeof(read_buf));
  printf("device says %s \n", read_buf);
  */
  close(fd);
  return 0;
}

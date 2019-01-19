#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#define PRINTCODE _IOW(241, 0, char*)

#define DEVICE "/dev/pratimdevice"

int main(){
  int i, fd;
  fd = open(DEVICE, O_RDWR);

  if (fd == -1){
    printf("File does not exist");
    exit(-1);
  }

  //ioctl(fd, PRINTCODE, "hi this is pratim ioctl");

  // writing to device

   /*char write_buf[100] = "Hi this is pratim";
  write(fd, write_buf, sizeof(write_buf));*/

  char read_buf[100];
  read(fd, read_buf, sizeof(read_buf));
  printf("device says %s \n", read_buf);

  return 0;
}

# kernel_basics

## ERRORS

1. Required key not available: Solution: disable Secure Boot in UEFI (BIOS) settings.
   Since Ubuntu kernel build 4.4.0-21.37 this can be fixed by running
   ```
   sudo apt install mokutil
   sudo mokutil --disable-validation
   ```

## Running Module
1. `make` to compile using Makefile
2. `sudo insmod 'module-name'.ko` to install the module
3. `dmesg` to display message

## Using the ARM Cross Compiler 
1. Install the arm-linux-gnueabi-gcc compiler
    ```
    sudo apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi
    ```
2. Install qemu-arm-static
   ```
    sudo apt-get install qemu binfmt-support qemu-user-static
   ```
3. Make the binary file:
    ```
    make CC=arm-linux-gnueabi-gcc
    ```
    The Makefile can be found here:
    https://github.com/jadonk/gsoc-application

4. Execute the binary using QEMU emulator:
     ```
     qemu-arm-static ./helloworld.bin
     ```


5. To compile a normal C program:
   ```
    arm-linux-gnueabi-gcc helloworld.c
   ```
   It will require to create a password. The password should be at least 8 characters long. After you reboot, UEFI will ask if you want to change security settings. Choose "Yes".
   
   Help :-
   https://sourceware.org/systemtap/wiki/SecureBoot
   
   https://askubuntu.com/questions/762254/why-do-i-get-required-key-not-available-when-install-3rd-party-kernel-modules

2. printk() not displaying message: 
   Solution: adding '\n' to the printed text on the display function
  
3. Could not open device file: This is because the file was created in superuser mode while using the mknod command.
   Refer to https://github.com/pratimugale/kernel_basics/issues/1. 

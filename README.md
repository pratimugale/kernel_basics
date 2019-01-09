# kernel_basics

## Running Module
1. `make` to compile using Makefile
2. `sudo insmod 'module-name'.ko` to install the module
3. `dmesg` to display message

## ERRORS

1. Required key not available: Solution: disable Secure Boot in UEFI (BIOS) settings.
   Since Ubuntu kernel build 4.4.0-21.37 this can be fixed by running
   ```
   sudo apt install mokutil
   sudo mokutil --disable-validation
   ```
   It will require to create a password. The password should be at least 8 characters long. After you reboot, UEFI will ask if you want to change security settings. Choose "Yes".
   
   Help :-
   https://sourceware.org/systemtap/wiki/SecureBoot
   
   https://askubuntu.com/questions/762254/why-do-i-get-required-key-not-available-when-install-3rd-party-kernel-modules

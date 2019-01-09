# kernel_basics

1. Error: Required key not available: Solution: disable Secure Boot in UEFI (BIOS) settings.
   Since Ubuntu kernel build 4.4.0-21.37 this can be fixed by running
   ```
   sudo apt install mokutil
   sudo mokutil --disable-validation
   ```
   It will require to create a password. The password should be at least 8 characters long. After you reboot, UEFI will ask if you want to change security settings. Choose "Yes".

# Kernel Implementation Documentation

## Installing the Kernel (version 3.19)

1. cd /usr/src/
2. wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.9.3.tar.xz
3. gunzip -d linux-3.19.tar.gz
4. tar svf linux-3.19.tar.gz
5. cd linux-3.19
6. yum install ncurses-devel ncurses
7. make menuconfig
8. [Right arrow over to "Save"]
9. [Right arrow to Exit]
10. make -j 20
11. make modules
12. make modules_install
13. make install
14. shutdown -r 0
15. uname -r

### Notes

#### If the system does not boot from the new kernel after being rebooted, do the following in iLO:
1. Open up the remote desktop
2. Press F11 to open up the "Boot Menu"
3. Select CentOS 3.19

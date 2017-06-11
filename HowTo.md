###RPI Kernel Compilation
Based on http://lostindetails.com/blog/post/Compiling-a-kernel-module-for-the-raspberry-pi-2

##On PI:
modprobe configs
udo zcat /proc/config.gz > \~/config
FIRMWARE_HASH=$(zgrep "* firmware as of" /usr/share/doc/raspberrypi-bootloader/changelog.Debian.gz | head -1 | awk '{ print $5 }')
KERNEL_HASH=$(wget https://raw.github.com/raspberrypi/firmware/$FIRMWARE_HASH/extra/git_hash -O -)
echo $KERNEL_HASH
mkdir \~/fbtft

##On Ubuntu:
mkdir \~/rpi
cd \~/rpi
sudo apt-get install crossbuild-essential-armhf
export CCPREFIX=/usr/bin/arm-linux-gnueabihf-
git clone https://github.com/raspberrypi/linux
export KERNEL_SRC=/home/${USER}/rpi/linux/ 
cd $KERNEL_SRC
git checkout $COPY_PAST_ABOVE_KERNEL_HASH
sudo scp pi@192.168.1.108:~/config $KERNEL_SRC/.config
make ARCH=arm CROSS_COMPILE=${CCPREFIX} oldconfig
make ARCH=arm CROSS_COMPILE=${CCPREFIX} -j3
make ARCH=arm CROSS_COMPILE=${CCPREFIX} modules -j3

#Deploy to PI:
scp \~/rpi/linux/drivers/video/fbtft/*.ko pi@192.168.1.108:~/fbtft

##Install and Test on PI
#install.sh:
```
#!/bin/bash
sudo rmmod fb_ra8875.ko -s
sudo rmmod fbtft_device.ko -s
sudo rmmod fbtft.ko -s
echo "Modules removed"
if [[ $1 == "1" ]]; then
        sudo insmod ~/fbtft/fbtft.ko
        sudo insmod ~/fbtft/fb_ra8875.ko
        sudo insmod ~/fbtft/fbtft_device.ko name="er_tftm070_48"
        echo "Modules installed"
fi
```
#Bash:
./fbtest --fbdev /dev/fb1

RPI Kernel Compilation
Based on http://lostindetails.com/blog/post/Compiling-a-kernel-module-for-the-raspberry-pi-2

On PI:
modprobe configs
udo zcat /proc/config.gz > ~/config
FIRMWARE_HASH=$(zgrep "* firmware as of" /usr/share/doc/raspberrypi-bootloader/changelog.Debian.gz | head -1 | awk '{ print $5 }')
KERNEL_HASH=$(wget https://raw.github.com/raspberrypi/firmware/$FIRMWARE_HASH/extra/git_hash -O -)
echo $KERNEL_HASH



On Ubuntu:
mkdir ~/rpi
cd ~/rpi
###git clone https://github.com/raspberrypi/tools
###export CCPREFIX=/home/${USER}/rpi/tools/arm-bcm2708/arm-bcm2708hardfp-linux-gnueabi/bin/arm-bcm2708hardfp-linux-gnueabi-
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

make ARCH=arm CROSS_COMPILE=$(PREFIX) -C /lib/modules/$(uname -r)/build M=$(pwd) modules

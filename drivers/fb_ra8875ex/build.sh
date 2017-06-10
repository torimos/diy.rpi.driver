make ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- -C ~/rpi/linux M=$(pwd) modules
echo "Cleaning up"
rm -f -r *.mod.* *.o *.symvers *.order .*.cmd .tmp_versions
echo "Publishing to remote PI"
sshpass -p "rpi1983" scp fb_ra8875ex.ko pi@192.168.1.108:.
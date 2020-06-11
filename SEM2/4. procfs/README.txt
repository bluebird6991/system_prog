1. in this folder workt
2. sudo rmmod CharDevice.ko
3. make
4. sudo insmod CharDevice.ko
5. echo "Hello" > /dev/chardev
6. cat /dev/chardev
$HOME/opt/cross/bin/i686-elf-as drivers/*.s -o asm.o
$HOME/opt/cross/bin/i686-elf-gcc -c drivers/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc --verbose -T drivers/test.ld -o test.bin -ffreestanding -O2 -nostdlib *.o -lgcc

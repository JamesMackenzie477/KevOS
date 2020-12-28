rm -d build
mkdir build
cd build
$HOME/opt/cross/bin/i686-elf-as ../*.s -o asm.o
$HOME/opt/cross/bin/i686-elf-gcc -c ../*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -c ../test/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -T ../kevin.ld -o test.bin -ffreestanding -O2 -nostdlib *.o -lgcc
rm *.o

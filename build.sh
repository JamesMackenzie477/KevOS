rm -r build
mkdir -p build/iso/boot/grub
cd build
$HOME/opt/cross/bin/i686-elf-as ../grub/*.s -o asm.o
$HOME/opt/cross/bin/i686-elf-gcc -c ../kernel/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -c ../kernel/sys/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -c ../kernel/memory/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -T ../linker.ld -o kevin.bin -ffreestanding -O2 -nostdlib *.o -lgcc
grub-file --is-x86-multiboot kevin.bin
cp kevin.bin iso/boot/kevin.bin
cp ../grub/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o kevin.iso iso
qemu-system-i386.exe -cdrom kevin.iso
cd ..

mkdir -p build/iso/boot/grub
cd build
$HOME/opt/cross/bin/i686-elf-as ../grub/boot.s -o boot.o
$HOME/opt/cross/bin/i686-elf-gcc -c ../kernel/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -T ../linker.ld -o kevin.bin -ffreestanding -O2 -nostdlib *.o -lgcc
grub-file --is-x86-multiboot kevin.bin
cp kevin.bin iso/boot/kevin.bin
cp ../grub/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o kevin.iso iso
qemu-system-i386.exe -cdrom kevin.iso
cd ..
rm -R build

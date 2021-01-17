rm -r build
mkdir -p build/iso/boot/grub
cd source
tar cvf ../build/disk.tar disk/
cd ../build
$HOME/opt/cross/bin/i686-elf-as ../source/asm/*.s -o asm.o
$HOME/opt/cross/bin/i686-elf-gcc -c ../source/*.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$HOME/opt/cross/bin/i686-elf-gcc -T ../source/linker.ld -o KevOS.bin -ffreestanding -O2 -nostdlib *.o -lgcc
grub-file --is-x86-multiboot KevOS.bin
cp KevOS.bin iso/boot/KevOS.bin
cp ../source/grub/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o KevOS.iso iso
rm *.o *.bin *.tar
rm -r iso
qemu-system-i386.exe -cdrom KevOS.iso
cd ..


@rem Generate asm files from C sources
smlrc -flat16 -I source -label 100 source\screen.c asmgen\screen.asm
smlrc -flat16 -I source -label 200 source\input.c asmgen\input.asm

smlrc -flat16 -I source source\main.c asmgen\main.asm

@rem Assemble main file into binary
@cd asmgen
nasm -f bin -o ..\koloro.bin main.asm
@cd ..

@rem Copy binary to virtual floppy disk
imdisk -a -f mikeos.img -m K:
copy koloro.bin K:\
imdisk -D -m K:
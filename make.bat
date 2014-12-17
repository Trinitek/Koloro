
@rem Generate asm files from C sources
smlrc -flat16 -I source -label 100 source\screen.c asmgen\screen.asm
smlrc -flat16 -I source -label 200 source\input.c asmgen\input.asm
smlrc -flat16 -I source -label 300 source\system.c asmgen\system.asm
smlrc -flat16 -I source -label 400 source\draw.c asmgen\draw.asm
smlrc -flat16 -I source -label 500 source\file.c asmgen\file.asm
smlrc -flat16 -I source -label 600 source\math.c asmgen\math.asm
smlrc -flat16 -I source -label 700 source\fixed.c asmgen\fixed.asm

smlrc -flat16 -I source source\main.c asmgen\main.asm

@rem Assemble main file into binary
@cd asmgen
nasm -f bin -o ..\koloro.bin main.asm
@cd ..

@rem Copy binary to virtual floppy disk
imdisk -a -f mikeos.img -m K:
copy koloro.bin K:\
imdisk -D -m K:
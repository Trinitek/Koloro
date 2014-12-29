
@rem Create output directories if they don't already exist
@rem Suppress error messages by redirecting them to the NUL device
@md asmgen 2> nul
@md bin 2> nul

@rem Generate asm files from C sources
smlrc -flat16 -I source/inc -label 100 source\screen.c asmgen\screen.asm
smlrc -flat16 -I source/inc -label 200 source\input.c asmgen\input.asm
smlrc -flat16 -I source/inc -label 300 source\system.c asmgen\system.asm
smlrc -flat16 -I source/inc -label 400 source\draw.c asmgen\draw.asm
smlrc -flat16 -I source/inc -label 500 source\file.c asmgen\file.asm
smlrc -flat16 -I source/inc -label 600 source\math.c asmgen\math.asm
smlrc -flat16 -I source/inc -label 700 source\fixed.c asmgen\fixed.asm
@rem smlrc -flat16 -I source/inc -label 800 source\state.c asmgen\state.asm
smlrc -flat16 -I source/inc -I font/inc -label 900 source\font.c asmgen\font.asm

smlrc -flat16 -I source/inc source\main.c asmgen\main.asm

@rem Assemble loader
fasm source\loader.asm bin\loader.bin

@rem Assemble program
@cd asmgen
nasm -f bin -o ..\bin\prog.bin ..\source\prog.asm
@cd ..\bin

@rem Assemble loader and program into final executable
nasm -f bin -o koloro.bin ..\source\koloro.asm
@cd ..

@rem Copy binary to virtual floppy disk
imdisk -a -f mikeos.img -m K:
copy bin\koloro.bin K:\
imdisk -D -m K:

@rem Generate asm files from C sources
smlrc -flat16 -label 100 screen.c screen.asm
smlrc -flat16 -label 200 input.c input.asm

smlrc -flat16 main.c main.asm

@rem Assemble main file into binary
nasm -o koloro.com main.asm
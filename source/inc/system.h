
#define OS_SEG          0x2000
#define PROGRAM_SEG     0x3000
#define VIDEO_SEG       0xA000

void outb(char port, char data);
void outw(char port, short data);
void mempokeb(short segment, short offset, char data);
void mempokew(short segment, short offset, short data);
char mempeekb(short segment, short offset);
short mempeekw(short segment, short offset);
void memcopy(short srcSeg, short srcOfs, short destSeg, short destOfs, short size);
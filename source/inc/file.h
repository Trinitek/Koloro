
#include "bool.h"

bool os_writeFile(short bufferOfs, short size);
short os_readFile();
bool saveFile(char *filenameStr_ptr, short sourceSeg, short sourceOfs, short size);
short loadFile(char *filenameStr_ptr, short destSeg, short destOfs);
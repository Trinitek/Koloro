
#include "bool.h"

bool os_writeFile(short bufferOfs, short size);
short os_readFile(char *filenameStr, char *array);
bool saveFile(char *filenameStr_ptr, short sourceSeg, short sourceOfs, short size);
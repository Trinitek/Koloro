
#ifndef _INPUT_H
#define _INPUT_H

#include "bool.h"

#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_ESC     27
#define KEY_ENTER   13

extern char mouse_data;

extern char mouse_dx;
extern char mouse_dy;

extern short mouse_rawX;
extern short mouse_rawY;

extern char mouse_scaleX;
extern char mouse_scaleY;

extern short mouse_posX;
extern short mouse_posY;

extern short mouse_minX;
extern short mouse_minY;

extern short mouse_limX;
extern short mouse_limY;

extern char mouse_buttonL;
extern char mouse_buttonM;
extern char mouse_buttonR;
extern char mouse_buttonOn;

extern short mouse_cursorX;
extern short mouse_cursorY;

extern bool mouse_changed;

extern char mouse_eventMode;

enum mouse_timeout { DATA, SIGNAL };

char getKey(void);
void waitForKey(void);
void mouseWait(enum mouse_timeout type);
char mouseRead(void);
void mouseInit(void);
void mouseInstall(void);
void mouseUninstall(void);
void mouseInterruptHandler(void);

#endif

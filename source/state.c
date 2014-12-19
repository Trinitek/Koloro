
#include "draw.h"

enum Tool {
    PENCIL,
    BRUSH,
    LINE,
    RECTANGLE,
    FILLED_RECTANGLE,
    CIRCLE,
    FILLED_CIRCLE
}

typedef struct {
    // The current tool being used.
    Tools tool;

    // The current color selected.
    char primaryColor;

    // The secondary color selected.
    char secondaryColor;
} currentState;

void useTool() {
    Tool state = currentState.tool;

    if(state == PENCIL) {
        pencil(mouseY(), mouseX(), currentState.primaryColor);
    }
}

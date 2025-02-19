
#ifndef UTILS_H
#define UTILS_H

/* 
 * TODO: review this code 
 */

// if #include "../include/raygui.h"
// I get ->  "redefinition of guiIcons""

// why I can add this and not raygui 
#include <raylib.h>

#define GRID_COLS 12
#define GRID_COLS_LEFT_OFFSET 2
#define GRID_COLS_RIGHT_OFFSET 2

#define GRID_ROWS 8
#define GRID_ROWS_TOP_OFFSET 1
#define GRID_ROWS_BOTTOM_OFFSET 3

#define GRID_PADDING 10
#define CELL_MARGIN 5

// forward declaration to avoid 
int GuiButton(Rectangle bounds, const char *text);

void GridLayout(int width, int height );

#endif 

#include "../include/utils.h"

void GridLayout(int width, int height) {

  Rectangle container = { .x = GRID_PADDING,
                          .y = GRID_PADDING,
                          .width = (float)width - 2 * GRID_PADDING,
                          .height = (float)height - 2 * GRID_PADDING };

  float cellWidth =
      (container.width - (float)GRID_PADDING * (float)(GRID_COLS + 1)) /
      (float)GRID_COLS;

  float cellHeight =
      (container.height - (float)GRID_PADDING * (float)(GRID_ROWS + 1)) /
      (float)GRID_ROWS;

  for (int row = GRID_ROWS_TOP_OFFSET;
       row < GRID_ROWS - GRID_ROWS_BOTTOM_OFFSET; row++) {
    for (int col = GRID_COLS_LEFT_OFFSET;
         col < (GRID_COLS - GRID_COLS_RIGHT_OFFSET); col++) {

      float cell_x =
          container.x + GRID_PADDING + (float)col * (cellWidth + GRID_PADDING);

      float cell_y =
          container.y + GRID_PADDING + (float)row * (cellHeight + GRID_PADDING);

      Rectangle cell = { cell_x, cell_y, cellWidth, cellHeight };

     
      GuiButton((Rectangle){ cell.x + CELL_MARGIN, cell.y + CELL_MARGIN,
                             cell.width - 2 * CELL_MARGIN,
                             cell.height - 2 * CELL_MARGIN },
                TextFormat("%d,%d", row, col));
    }
  }
}

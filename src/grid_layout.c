#include "../include/utils.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

void Grid_Layout(JournalC99 *journalC99)
{
  float width = (float)GetScreenWidth();
  float height = (float)GetScreenHeight();

  Rectangle container = {.x = GRID_PADDING,
                         .y = GRID_PADDING,
                         .width = width - 2 * GRID_PADDING,
                         .height = height - 2 * GRID_PADDING};

  float cellWidth =
      (container.width - GRID_PADDING * (GRID_COLS + 1.0F)) / GRID_COLS;
  float cellHeight =
      (container.height - GRID_PADDING * (GRID_ROWS + 1.0F)) / GRID_ROWS;

  int(*map)[12] = Return_Map_Pr(journalC99->currentState);

  size_t size_row = 5;
  size_t size_col = 12;

  for (size_t row = 0; row < size_row; row++)
  {

    for (size_t col = 0; col < size_col; col++)
    {

      float cell_x = (container.x + GRID_PADDING +
                      (float)col * (cellWidth + GRID_PADDING)) +
                     CELL_MARGIN;

      float cell_y = (container.y + GRID_PADDING +
                      (float)row * (cellHeight + GRID_PADDING)) +
                     CELL_MARGIN;

      Rectangle cell = {cell_x, cell_y, cellWidth, cellHeight};

      switch (map[row][col])
      {

      case ELMNT_BTN_B:
        if (GuiButton((Rectangle){cell.x, cell.y, cell.width - 2 * CELL_MARGIN,
                                  cell.height - 2 * CELL_MARGIN},
                      TextFormat("B: %d,%d ", row, col)))
        {
          Update_State(journalC99, evt_btn_month);
        }
        break;
      case ELMNT_BTN_C:
        if (GuiButton((Rectangle){cell.x, cell.y, cell.width - 2 * CELL_MARGIN,
                                  cell.height - 2 * CELL_MARGIN},
                      TextFormat("C: %d,%d", row, col)))
        {
          Update_State(journalC99, evt_btn_today);
        }
        break;
      default:
        break;
      }
    }
  }
}

#include "../include/utils.h"
#include "raylib.h"
#include <stddef.h>

void Grid_Layout(JournalC99 *journalC99)
{
  const float width = (float)GetScreenWidth();
  const float height = (float)GetScreenHeight();

  extern char *current_month_name;
  extern char *current_day_name;
  extern char current_day_number[3];


  Color font_color = GetColor(GuiGetStyle(0, 2));

  // TODO: fix this, maybe use DrawTextEx ???
  int fontSize = height * 0.02f;

  const Rectangle container = {.x = GRID_PADDING,
                               .y = GRID_PADDING,
                               .width = width - 2 * GRID_PADDING,
                               .height = height - 2 * GRID_PADDING};

  const float cellWidth =
      (container.width - GRID_PADDING * (GRID_COLS + 1.0F)) / GRID_COLS;
  const float cellHeight =
      (container.height - GRID_PADDING * (GRID_ROWS + 1.0F)) / GRID_ROWS;

  const int(*map)[12] = Return_Map_Pr(journalC99->currentState);

  int i = 1;
  for (int row = 0; row < SIZE_ROW; row++)
  {

    for (int col = 0; col < SIZE_COL; col++)
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
      case TOGGLE_GROUP:
      {
        int stateOffset = 1;
        /*
         * -1 because  STATE_TABLE start at [0]: INVALID_STATE
         *  and Update_State->nextState == 0
         *  when there is no explicit transition in
         *  the transition_table (when this doesn't  exist [state] = {state ...}
         */
        int temp = ((int)journalC99->currentState) - stateOffset;

        GuiToggleGroup((Rectangle){cell.x, cell.y, cell.width - 2 * CELL_MARGIN,
                                   cell.height - 2 * CELL_MARGIN},
                       "TODAY;MONTH;YEAR;GRAPH", &temp);

        /*
         * -1 because  STATE_TABLE start at [0]: INVALID_STATE
         *  and Update_State->nextState == 0
         *  when there is no explicit transition in
         *  the transition_table (when this doesn't  exist [state] = {state ...}
         */
        if (temp != ((int)journalC99->currentState) - stateOffset)
        {
          /*
            Event(temp):
            order of EVENT_TABLE and
            GuiToggleGroup(..., "TODAY;MONTH;YEAR;GRAPH", ...);
            should be the same.
           */
          Update_State(journalC99, (Event)temp);
        }

        break;
      }
      case ELMNT_DAY:
        if (GuiButton((Rectangle){cell.x, cell.y, cell.width - 2 * CELL_MARGIN,
                                  cell.height - 2 * CELL_MARGIN},
                      TextFormat("%d", i++)))

        {
          Update_State(journalC99, evt_btn_today);
        }

        break;

      case ELMNT_SUNDAY:
        DrawText("Sun", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;

      case ELMNT_MONDAY:
        DrawText("Mon", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;

      case ELMNT_TUESDAY:
        DrawText("Tues", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;

      case ELMNT_WEDNESDAY:
        DrawText("Wednes", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;

      case ELMNT_THURSDAY:
        DrawText("Thurs", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;
      case ELMNT_FRIDAY:
        DrawText("Fri", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;
      case ELMNT_SATURDAY:
        DrawText("Sat", (int)cell.x, (int)cell.y, fontSize, font_color);
        break;
      case ELMNT_MONTH:
        DrawText(current_month_name, (int)cell.x, (int)cell.y, fontSize * 2,
                 font_color);
        break;
      case ELMNT_TEXT:
        DrawText(current_month_name, (int)cell.x, (int)cell.y, 32, RAYWHITE);
        break;

      case ELMNT_CURR_DAY_NAME:
        DrawText(current_day_name, (int)cell.x, (int)cell.y, fontSize * 2,
                 font_color);
        break;

      case ELMNT_CURR_DAY_NUMBER:
        DrawText(current_day_number, (int)cell.x, (int)cell.y, fontSize * 2,
                 font_color);
        break;

      default:
        break;
      }
    }
  }
}

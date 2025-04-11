#include "../include/utils.h"
#include "raylib.h"

#include <stdbool.h>
#include <stdio.h>

#define X(state) #state,
char *state_name[] = {STATE_TABLE};
#undef X

#define X(event) #event,
char *event_name[] = {EVENT_TABLE};
#undef X

#define X(element) #element,
char *element_list[] = {ELEMENT_LIST};
#undef X

State transition_table[NUM_STATES][NUM_EVENTS] = {
    /*             evt_btn_today | evt_btn_month | evt_btn_year | evt_btn_graph
     */
    [STATE_ROOT_TODAY] = {INVALID_STATE, STATE_MONTH, STATE_YEAR, STATE_GRAPH},
    [STATE_MONTH] = {STATE_ROOT_TODAY, INVALID_STATE, STATE_YEAR, STATE_GRAPH},
};

State Update_State(JournalC99 *journalC99, Event event)
{

  State currentState = journalC99->currentState;
  State nextState = transition_table[currentState][event] != INVALID_STATE
                        ? transition_table[currentState][event]
                        : currentState;

  //  printf("|%10s|%10s|%10s|\n", state_name[currentState],
  //  event_name[event],state_name[nextState]);

  return journalC99->currentState = nextState;
}

int (*Return_Map_Pr(State state))[12]
{

  static int map[5][12] = {0};

  static int map_state_root_today[5][12] = {{
                                                ELMNT_BLANK,
                                            },
                                            {
                                                ELMNT_BLANK,
                                                ELMNT_BLANK,
                                                ELMNT_BTN_B,
                                            }};

  static int map_state_month[5][12] = {{
                                           ELMNT_BLANK,
                                       },
                                       {
                                           ELMNT_BLANK,
                                           ELMNT_BLANK,
                                           ELMNT_BTN_C,
                                       }};

  static int map_state_year[5][12] = {{
                                          ELMNT_BLANK,
                                      },
                                      {
                                          ELMNT_BLANK,
                                          ELMNT_BLANK,
                                          ELMNT_BTN_C,
                                      }};

  static int map_state_graph[5][12] = {{
                                           ELMNT_BLANK,
                                       },
                                       {
                                           ELMNT_BLANK,
                                           ELMNT_BLANK,
                                           ELMNT_BTN_C,
                                       }};

  switch (state)
  {
  case STATE_ROOT_TODAY:
    return map_state_root_today;
  case STATE_MONTH:
    return map_state_month;
  case STATE_YEAR:
    return map_state_year;
  case STATE_GRAPH:
    return map_state_graph;
  case INVALID_STATE:
  case NUM_STATES:;
  }

  return map;
}

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

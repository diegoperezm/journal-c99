#include "../include/utils.h"
#include "raylib.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define X(state) #state,
char* state_name[] = { STATE_TABLE };
#undef X

#define X(event) #event,
char* event_name[] = { EVENT_TABLE };
#undef X

#define X(element) #element,
char* element_list[] = { ELEMENT_LIST };
#undef X

State transition_table[NUM_STATES][NUM_EVENTS] = {
  /*             evt_btn_today | evt_btn_month | evt_btn_year | evt_btn_graph */
  [STATE_WAITING] = { STATE_ROOT_TODAY, STATE_MONTH, STATE_YEAR, STATE_GRAPH },
  [STATE_ROOT_TODAY] = { INVALID_STATE, STATE_MONTH, STATE_YEAR, STATE_GRAPH },
  [STATE_MONTH] = { STATE_ROOT_TODAY, INVALID_STATE, STATE_YEAR, STATE_GRAPH },
};

void Update_State(JournalC99* journalC99, Event event) {

  State currentState = journalC99->currentState;
  State nextState = transition_table[currentState][event];

  //  printf("|%10s|%10s|%10s|\n", state_name[currentState], event_name[event],
  //        state_name[nextState]);

  if (nextState != INVALID_STATE) {

    journalC99->currentState = nextState;

    switch (nextState) {

    case STATE_ROOT_TODAY:
      DrawText("today", 10, 20, 100, WHITE);
      break;

    case STATE_MONTH:
      DrawText("month", 10, 20, 100, WHITE);
      break;

    case STATE_YEAR:
      DrawText("year", 10, 20, 100, WHITE);
      break;

    case STATE_GRAPH:
      DrawText("graph", 10, 20, 100, WHITE);
      break;

    default:
      break;
    }
  }
}

void GridLayout(JournalC99* journalC99) {
  float width = (float)GetScreenWidth();
  float height = (float)GetScreenHeight();

  int map[5][12] = { {
                         ELMNT_BLANK,
                     },
                     {
                         ELMNT_BLANK,
                         ELMNT_BLANK,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                         ELMNT_BTN_B,
                     } };

  Rectangle container = { .x = GRID_PADDING,
                          .y = GRID_PADDING,
                          .width = width - 2 * GRID_PADDING,
                          .height = height - 2 * GRID_PADDING };

  float cellWidth =
      (container.width - GRID_PADDING * (GRID_COLS + 1.0F)) / GRID_COLS;
  float cellHeight =
      (container.height - GRID_PADDING * (GRID_ROWS + 1.0F)) / GRID_ROWS;

  size_t size_row = sizeof(map) / sizeof(map[0]);
  size_t size_col = sizeof(map[0]) / sizeof(map[0][0]);

  for (int row = 0; row < size_row; row++) {
    for (int col = 0; col < size_col; col++) {

      float cell_x = (container.x + GRID_PADDING +
                      (float)col * (cellWidth + GRID_PADDING)) +
                     CELL_MARGIN;

      float cell_y = (container.y + GRID_PADDING +
                      (float)row * (cellHeight + GRID_PADDING)) +
                     CELL_MARGIN;

      Rectangle cell = { cell_x, cell_y, cellWidth, cellHeight };

      switch (map[row][col]) {

      case ELMNT_BTN_B:
        if (GuiButton((Rectangle){ cell.x, cell.y, cell.width - 2 * CELL_MARGIN,
                                   cell.height - 2 * CELL_MARGIN },
                      TextFormat("%d,%d", row, col))) {

          Update_State(journalC99, evt_btn_month);
        }

      default:
        break;
      }

      // printf("%s %d\n", element_list[map[row][col]], (int)cell.x);
    }
  }
}

void GridLayout2() {
  float width = (float)GetScreenWidth();
  float height = (float)GetScreenHeight();

  Rectangle container = { .x = GRID_PADDING,
                          .y = GRID_PADDING,
                          .width = width - GRID_PADDING,
                          .height = height - GRID_PADDING };

  float cellWidth =
      (container.width - GRID_PADDING * (GRID_COLS + 1)) / GRID_COLS;

  float cellHeight =
      (container.height - GRID_PADDING * (GRID_ROWS + 1)) / GRID_ROWS;

  for (int row = GRID_ROWS_TOP_OFFSET;
       row < GRID_ROWS - GRID_ROWS_BOTTOM_OFFSET; row++) {
    for (int col = GRID_COLS_LEFT_OFFSET;
         col < (GRID_COLS - GRID_COLS_RIGHT_OFFSET); col++) {

      float cell_x = (container.x + GRID_PADDING +
                      (float)col * (cellWidth + GRID_PADDING)) +
                     CELL_MARGIN;

      float cell_y = (container.y + GRID_PADDING +
                      (float)row * (cellHeight + GRID_PADDING)) +
                     CELL_MARGIN;

      Rectangle cell = { cell_x, cell_y, cellWidth, cellHeight };

      GuiButton((Rectangle){ cell.x + CELL_MARGIN, cell.y + CELL_MARGIN,
                             cell.width - 2 * CELL_MARGIN,
                             cell.height - 2 * CELL_MARGIN },
                TextFormat("%d,%d", row, col));
    }
  }
}

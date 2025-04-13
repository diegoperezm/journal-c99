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
    //[STATE_GRAPH] = {INVALID_STATE, INVALID_STATE, INVALID_STATE,
    //                INVALID_STATE},
};

State Update_State(JournalC99 *journalC99, Event event)
{

  State currentState = journalC99->currentState;
  State nextState = transition_table[currentState][event] != INVALID_STATE
                        ? transition_table[currentState][event]
                        : currentState;

  //  printf("|%10s|%10s|%10s|\n", state_name[currentState], event_name[event],
  //        state_name[nextState]);

  return journalC99->currentState = nextState;
}

int (*Return_Map_Pr(State state))[12]
{

  int calendar[6][7] = {0};
  int start_col = 1;
  int days_in_month = 30;
  int day = 1;

  for (int i = 0; i < 6 && day <= days_in_month; i++)
  {
    for (int j = 0; j < 7 && day <= days_in_month; j++)
    {
      if (i == 0 && j < start_col)
        continue;
      calendar[i][j] = day;
      day++;
    }
  }

  static int map[5][12] = {0};

  static int map_state_root_today[6][12] = {
      {
          TOGGLE_GROUP,
      },
  };

  static int map_state_month[6][12] = {
      {
          TOGGLE_GROUP,
      },
  };

  // Insert calendar into map_state_month
  int grid_row_offset = 1; // Start placing in row 1 of the grid
  int grid_col_offset = 2; // Start

  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (calendar[i][j] != 0)
      {
        int grid_row = grid_row_offset + i;
        int grid_col = grid_col_offset + j;

        if (grid_row < 6 && grid_col < 12)
        {
          map_state_month[grid_row][grid_col] = ELMNT_DAY;
        }
      }
    }
  }

  static int map_state_year[5][12] = {{
                                          TOGGLE_GROUP,

                                      },
                                      {
                                          ELMNT_BLANK,
                                          ELMNT_BLANK,
                                          BTN_C,
                                      }};

  static int map_state_graph[5][12] = {{
                                           TOGGLE_GROUP,
                                       },
                                       {
                                           ELMNT_BLANK,
                                           ELMNT_BLANK,
                                           BTN_C,
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

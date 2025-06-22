#include "../include/utils.h"

#include <stdio.h>
#include <sys/types.h>
#include <time.h>

#define X(state) #state,
char *state_name[] = {STATE_TABLE};
#undef X

#define X(event) #event,
char *event_name[] = {EVENT_TABLE};
#undef X

#define X(element) #element,
char *element_list[] = {ELEMENT_LIST};
#undef X

char *month[12] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December",
};

char *daysOfWeek[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                      "Thursday", "Friday", "Saturday"};

uint8_t days_in_month[12] = {
    31, // January
    28, // February (2025 is not a leap year)
    31, // March
    30, // April
    31, // May
    30, // June
    31, // July
    31, // August
    30, // September
    31, // October
    30, // November
    31  // December
};

uint8_t first_day_in_month[12] = {
    3, // January 1, 2025, is Wednesday
    6, // February 1, 2025, is Saturday
    6, // March 1, 2025, is Saturday
    2, // April 1, 2025, is Tuesday
    4, // May 1, 2025, is Thursday
    0, // June 1, 2025, is Sunday
    2, // July 1, 2025, is Tuesday
    5, // August 1, 2025, is Friday
    1, // September 1, 2025, is Monday
    3, // October 1, 2025, is Wednesday
    6, // November 1, 2025, is Saturday
    1  // December 1, 2025, is Monday
};

char *current_month_name = NULL;
char *current_day_name   = NULL;
char current_day_number[3] = {0};

State transition_table[NUM_STATES][NUM_EVENTS] = {

    /*             evt_btn_today | evt_btn_month | evt_btn_year | evt_btn_graph
     */
    [STATE_ROOT_TODAY] = {INVALID_STATE, STATE_MONTH, STATE_YEAR, STATE_GRAPH},
    [STATE_MONTH] = {STATE_ROOT_TODAY, INVALID_STATE, STATE_YEAR, STATE_GRAPH},
    [STATE_YEAR] = {STATE_ROOT_TODAY, STATE_MONTH, INVALID_STATE, STATE_GRAPH},
    [STATE_GRAPH] = {STATE_ROOT_TODAY, STATE_MONTH, STATE_YEAR, INVALID_STATE},

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

int (*Return_Map_Pr(const State state))[12]
{
  static int map[5][12] = {0};
  time_t now = time(NULL);
  struct tm *tm_now = localtime(&now);
  snprintf(current_day_number, sizeof(current_day_number), "%u",
           tm_now->tm_mday);
  uint8_t current_week_day = (uint8_t)tm_now->tm_wday;
  uint8_t current_month = (uint8_t)tm_now->tm_mon;
  current_month_name = month[current_month];
  current_day_name = daysOfWeek[current_week_day];
  uint8_t day = 1;

  static int map_state_root_today[SIZE_ROW][SIZE_COL] = {
      {
          TOGGLE_GROUP,
      },
      {ELMNT_MONTH, ELMNT_CURR_DAY_NAME, ELMNT_BLANK, ELMNT_CURR_DAY_NUMBER}};

  static int map_state_month[SIZE_ROW][SIZE_COL] = {
      {
          TOGGLE_GROUP,
      },
      {
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_MONTH,
      },
      {
          ELMNT_BLANK,
          ELMNT_BLANK,
          ELMNT_SUNDAY,
          ELMNT_MONDAY,
          ELMNT_TUESDAY,
          ELMNT_WEDNESDAY,
          ELMNT_THURSDAY,
          ELMNT_FRIDAY,
          ELMNT_SATURDAY,
      },

  };

  static int map_state_year[SIZE_ROW][SIZE_COL] = {
      {
          TOGGLE_GROUP,

      },
  };

  static int map_state_graph[SIZE_ROW][SIZE_COL] = {
      {
          TOGGLE_GROUP,
      },
  };

  switch (state)
  {
  case STATE_ROOT_TODAY:
    return map_state_root_today;

  case STATE_MONTH:
    for (int i = 0; i < 5; ++i)
    {
      for (int j = 0; j < 7 && day <= days_in_month[current_month]; ++j)
      {
        if (i == 0 && j < first_day_in_month[current_month])
          continue;
        map_state_month[i + 3][j + 2] = ELMNT_DAY;
        day++;
      }
    }
    return map_state_month;

  case STATE_YEAR:
    return map_state_year;

  case STATE_GRAPH:
    return map_state_graph;
  case INVALID_STATE:
    break;
  case NUM_STATES:;
    break;
  }

  return map;
}
/*
  printf("----\n");
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      printf("%d", map_state_month[i][j]);
    }
    printf("\n");
  }
*/

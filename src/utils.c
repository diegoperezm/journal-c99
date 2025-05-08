#include "../include/utils.h"
#include "raylib.h"
#include <bits/types/time_t.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#define MAX_PROJECTS 4
#define MAX_MONTHS 12
#define MAX_DAYS_IN_MONTH 31
#define MAX_PROJECT_NAME_LEN 64
#define MAX_COMMENT_LEN 256
#define MAX_TIME_STRING_LEN 6

typedef struct
{
  uint8_t hours;
  uint8_t minutes;
} Time;

typedef struct
{
  char name[MAX_PROJECT_NAME_LEN];
  Time duration;
} ProjectTime;

typedef struct
{
  char currentDayName[10];
  char currentMonthName[10];
  char currentDayNumber[3];
  char comments[MAX_COMMENT_LEN];

  char start[MAX_PROJECTS][MAX_TIME_STRING_LEN];
  char end[MAX_PROJECTS][MAX_TIME_STRING_LEN];
  char project[MAX_PROJECTS][MAX_TIME_STRING_LEN];
  Time totalHrs;
} DayEntry;

typedef struct
{
  uint8_t dayNumber;
  ProjectTime projectTimes[MAX_PROJECTS];
  uint8_t projectCount;
} DayliSummary;

typedef struct
{
  char monthName[10];
  DayliSummary days[MAX_DAYS_IN_MONTH];
  uint8_t dayCount;
  ProjectTime totalTime[MAX_PROJECTS];
  uint8_t projectCount;
} MonthSummary;

typedef struct
{
  DayEntry today;
  DayEntry daysByMonth[MAX_MONTHS][MAX_DAYS_IN_MONTH];
  MonthSummary year[MAX_MONTHS];
} Data;

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

int8_t get_days_in_month(time_t *time_now);

int8_t get_days_in_month(time_t *time_now)
{
  struct tm *now = localtime(time_now);
  int current_month_number = now->tm_mon;

  struct tm date = {0};

  date.tm_year = now->tm_year;

  // use next month
  date.tm_mon = current_month_number;

  // day 0 from next month = last day of the current month
  date.tm_mday = 0;

  if (mktime(&date) == -1)
  {
    if (errno == EINVAL)
    {
      printf("Error: Invalid date (EINVAL)\n");
    }
    else
    {
      printf("Error: %s\n", strerror(errno));
    }

    return -1; // error
  }

  return (int8_t)(date.tm_mday - 1);
}

int (*Return_Map_Pr(State state))[12]
{

  static int map[5][12] = {0};

  time_t now = time(NULL);
  int8_t days_in_month = get_days_in_month(&now);

  struct tm *nnow = localtime(&now);

  uint8_t current_day = (uint8_t)nnow->tm_wday;
  int day = 1;
  int first_week_day_in_month = 2;

  static int map_state_month[12][12] = {
      {
          TOGGLE_GROUP,
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

  static int map_state_root_today[12][12] = {
      {
          TOGGLE_GROUP,
      },
  };

  static int map_state_year[12][12] = {
      {
          TOGGLE_GROUP,

      },
  };

  static int map_state_graph[12][12] = {
      {
          TOGGLE_GROUP,
      },
  };

  switch (state)
  {
  case STATE_ROOT_TODAY:
    printf("%d", current_day);
    map_state_root_today[2][current_day] = ELMNT_DAY;
    return map_state_root_today;

  case STATE_MONTH:
    for (int i = 0; i < 5 && day <= days_in_month; ++i)
    {
      for (int j = 0; j < 7 && day <= days_in_month; ++j)
      {
        if (i == 0 && j < first_week_day_in_month)
        {
          continue; // Saltar hasta el primer día real del mes
        }
        map_state_month[i + 2][j + 2] = ELMNT_DAY;
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

#include <raylib.h>
#include "../include/raygui.h"
#include "../include/style_cyber.h"
#include "../include/utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
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

// @formatter:off
char *days_of_week_year_2025[365] = {
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Jan 1-7
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Jan 8-14
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Jan 15-21
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Jan 22-28
    "Wednesday", "Thursday", "Friday",                                             // Jan 29-31

    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Feb 1-7
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Feb 8-14
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Feb 15-21
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Feb 22-28

    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Mar 1-7
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Mar 8-14
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Mar 15-21
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Mar 22-28
    "Saturday", "Sunday", "Monday",                                                // Mar 29-31

    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Apr 1-7
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Apr 8-14
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Apr 15-21
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Apr 22-28
    "Tuesday", "Wednesday",                                                        // Apr 29-30

    "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",  // May 1-7
    "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",  // May 8-14
    "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",  // May 15-21
    "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",  // May 22-28
    "Thursday", "Friday", "Saturday",                                              // May 29-31

    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",  // Jun 1-7
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",  // Jun 8-14
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",  // Jun 15-21
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",  // Jun 22-28
    "Sunday", "Monday",                                                            // Jun 29-30

    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Jul 1-7
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Jul 8-14
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Jul 15-21
    "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday",  // Jul 22-28
    "Tuesday", "Wednesday", "Thursday",                                            // Jul 29-31

    "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",  // Aug 1-7
    "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",  // Aug 8-14
    "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",  // Aug 15-21
    "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",  // Aug 22-28
    "Friday", "Saturday", "Sunday",                                                // Aug 29-31

    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Sep 1-7
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Sep 8-14
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Sep 15-21
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Sep 22-28
    "Monday", "Tuesday",                                                           // Sep 29-30

    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Oct 1-7
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Oct 8-14
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Oct 15-21
    "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday",  // Oct 22-28
    "Wednesday", "Thursday", "Friday",                                             // Oct 29-31

    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Nov 1-7
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Nov 8-14
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Nov 15-21
    "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",  // Nov 22-28
    "Saturday", "Sunday",                                                          // Nov 29-30

    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Dec 1-7
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Dec 8-14
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Dec 15-21
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",  // Dec 22-28
    "Monday", "Tuesday", "Wednesday"                                               // Dec 29-31
};
// @formatter:off


// @formatter:off
char *month_for_each_day_2025[365] = {
    // January (31 days)
    "January", "January", "January", "January", "January", "January", "January",
    "January", "January", "January", "January", "January", "January", "January",
    "January", "January", "January", "January", "January", "January", "January",
    "January", "January", "January", "January", "January", "January", "January",
    "January", "January", "January",
    
    // February (28 days - 2025 is not a leap year)
    "February", "February", "February", "February", "February", "February", "February",
    "February", "February", "February", "February", "February", "February", "February",
    "February", "February", "February", "February", "February", "February", "February",
    "February", "February", "February", "February", "February", "February", "February",
    
    // March (31 days)
    "March", "March", "March", "March", "March", "March", "March",
    "March", "March", "March", "March", "March", "March", "March",
    "March", "March", "March", "March", "March", "March", "March",
    "March", "March", "March", "March", "March", "March", "March",
    "March", "March", "March",
    
    // April (30 days)
    "April", "April", "April", "April", "April", "April", "April",
    "April", "April", "April", "April", "April", "April", "April",
    "April", "April", "April", "April", "April", "April", "April",
    "April", "April", "April", "April", "April", "April", "April",
    "April", "April",
    
    // May (31 days)
    "May", "May", "May", "May", "May", "May", "May",
    "May", "May", "May", "May", "May", "May", "May",
    "May", "May", "May", "May", "May", "May", "May",
    "May", "May", "May", "May", "May", "May", "May",
    "May", "May", "May",
    
    // June (30 days)
    "June", "June", "June", "June", "June", "June", "June",
    "June", "June", "June", "June", "June", "June", "June",
    "June", "June", "June", "June", "June", "June", "June",
    "June", "June", "June", "June", "June", "June", "June",
    "June", "June",
    
    // July (31 days)
    "July", "July", "July", "July", "July", "July", "July",
    "July", "July", "July", "July", "July", "July", "July",
    "July", "July", "July", "July", "July", "July", "July",
    "July", "July", "July", "July", "July", "July", "July",
    "July", "July", "July",
    
    // August (31 days)
    "August", "August", "August", "August", "August", "August", "August",
    "August", "August", "August", "August", "August", "August", "August",
    "August", "August", "August", "August", "August", "August", "August",
    "August", "August", "August", "August", "August", "August", "August",
    "August", "August", "August",
    
    // September (30 days)
    "September", "September", "September", "September", "September", "September", "September",
    "September", "September", "September", "September", "September", "September", "September",
    "September", "September", "September", "September", "September", "September", "September",
    "September", "September", "September", "September", "September", "September", "September",
    "September", "September",
    
    // October (31 days)
    "October", "October", "October", "October", "October", "October", "October",
    "October", "October", "October", "October", "October", "October", "October",
    "October", "October", "October", "October", "October", "October", "October",
    "October", "October", "October", "October", "October", "October", "October",
    "October", "October", "October",
    
    // November (30 days)
    "November", "November", "November", "November", "November", "November", "November",
    "November", "November", "November", "November", "November", "November", "November",
    "November", "November", "November", "November", "November", "November", "November",
    "November", "November", "November", "November", "November", "November", "November",
    "November", "November",
    
    // December (31 days)
    "December", "December", "December", "December", "December", "December", "December",
    "December", "December", "December", "December", "December", "December", "December",
    "December", "December", "December", "December", "December", "December", "December",
    "December", "December", "December", "December", "December", "December", "December",
    "December", "December", "December"
};
// @formatter:off

// @formatter:off
int number_days_in_every_month_of_year_2025[365] = {
    // January (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // February (28 days) - days 1 to 28 (2025 is not a leap year)
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    
    // March (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // April (30 days) - days 1 to 30
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    
    // May (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // June (30 days) - days 1 to 30
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    
    // July (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // August (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // September (30 days) - days 1 to 30
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    
    // October (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    
    // November (30 days) - days 1 to 30
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    
    // December (31 days) - days 1 to 31
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};
// @formatter:off



char *month[12] = { 
  "January", "February", "March",     "April",   "May",      "June",
  "July",    "August",   "September", "October", "November", "December",
};

char *daysOfWeek[] = {
 "Sunday",   "Monday", "Tuesday", "Wednesday",
 "Thursday", "Friday", "Saturday"
};

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


uint16_t offset_days_in_month[12] = {
    0, // January
    31, // February (2025 is not a leap year)
    59, // March
    90, // April
    120, // May
    151, // June
    182, // July
    212, // August
    243, // September
    273,// October 
    304,// November 
    334,// December 
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

uint8_t current_month  = 0; 
char *current_month_name = NULL;
char *current_day_name   = NULL;
char current_day_number[3] = {0};
char selected_cal_day_number[3] = {0};

// @formatter:off
State transition_table[NUM_STATES][NUM_EVENTS] = {

    /*                    evt_btn_today | evt_btn_month | evt_btn_year | evt_btn_graph | evt_btn_cal_day
     */
    [STATE_ROOT_TODAY] = {INVALID_STATE,    STATE_MONTH,   STATE_YEAR,    STATE_GRAPH,   INVALID_STATE},
    [STATE_MONTH]      = {STATE_ROOT_TODAY, INVALID_STATE, STATE_YEAR,    STATE_GRAPH,   STATE_CAL_DAY},
    [STATE_YEAR]       = {STATE_ROOT_TODAY, STATE_MONTH,   INVALID_STATE, STATE_GRAPH,   STATE_CAL_DAY},
    [STATE_GRAPH]      = {STATE_ROOT_TODAY, STATE_MONTH,   STATE_YEAR,    INVALID_STATE, INVALID_STATE},
    [STATE_CAL_DAY]    = {STATE_ROOT_TODAY, STATE_MONTH,   STATE_YEAR,    STATE_GRAPH,   INVALID_STATE},

};
// @formatter:off
State Update_State(JournalC99 *journalC99, Event event)
{

  State currentState = journalC99->currentState;
  State nextState = transition_table[currentState][event] != INVALID_STATE
                        ? transition_table[currentState][event]
                        : currentState;

  printf("|%10s|%10s|%10s|\n", state_name[currentState], event_name[event], state_name[nextState]);
  return journalC99->currentState = nextState;
}

int (*Return_Map_Pr(const State state))[SIZE_ROWS][SIZE_COLS] {
  static int map[SIZE_ROWS][SIZE_COLS] = {0};

  time_t now = time(NULL);
  struct tm *tm_now = localtime(&now);

  snprintf(current_day_number, sizeof(current_day_number), "%u", tm_now->tm_mday);

  uint8_t current_week_day = (uint8_t)tm_now->tm_wday;
  current_month = (uint8_t)tm_now->tm_mon;
  current_month_name = month[current_month];
  current_day_name = daysOfWeek[current_week_day];
  uint8_t day = 1;

  static int map_state_root_today[SIZE_ROWS][SIZE_COLS] = {
      {TOGGLE_GROUP },
      {ELMNT_BLANK},
      {ELMNT_BLANK,ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_MONTH,ELMNT_BLANK, 
       ELMNT_CURR_DAY_NAME, ELMNT_BLANK, ELMNT_CURR_DAY_NUMBER},
      {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},
      {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},   
      {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},
 };
  
  static int map_state_month[SIZE_ROWS][SIZE_COLS] = {
      {
          TOGGLE_GROUP,
      },
          {ELMNT_BLANK},
      {
          ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_MONTH,
      },
      {ELMNT_BLANK},
     { ELMNT_BLANK, ELMNT_BLANK,ELMNT_BLANK, ELMNT_SUNDAY, ELMNT_MONDAY, ELMNT_TUESDAY,
       ELMNT_WEDNESDAY, ELMNT_THURSDAY, ELMNT_FRIDAY, ELMNT_SATURDAY},
     {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},{ELMNT_BLANK},{ELMNT_BLANK},{ELMNT_BLANK},
  };

  static int map_state_year[SIZE_ROWS][SIZE_COLS] = {
      {
          TOGGLE_GROUP,
      },
  };

  static int map_state_graph[SIZE_ROWS][SIZE_COLS] = {
      {
          TOGGLE_GROUP,
      },
  };

 static int  map_state_cal_day[SIZE_ROWS][SIZE_COLS] = {
      {TOGGLE_GROUP },
      {ELMNT_BLANK},
      {ELMNT_BLANK,ELMNT_BLANK, ELMNT_BLANK, ELMNT_BLANK, ELMNT_SELECTED_CAL_MONTH,ELMNT_BLANK,
       ELMNT_SELECTED_CAL_DAY, ELMNT_BLANK, ELMNT_SELECTED_CAL_DAY_NUMBER},
      {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},    
      {ELMNT_BLANK}, {ELMNT_BLANK}, {ELMNT_BLANK},
 };


  switch (state) {
  case STATE_ROOT_TODAY:
    return &map_state_root_today;

  case STATE_MONTH:
    for (int i = 0; i < 5; ++i)
    {
      for (int j = 0; j < 7 && day <= days_in_month[current_month]; ++j)
      {
        const int offset_row = 5;
        const int offset_col = 3;
        if (i == 0 && j < first_day_in_month[current_month])
          continue;
        map_state_month[i+offset_row][j+offset_col] = ELMNT_CAL_DAY;
        day++;
      }
    }
    return &map_state_month;

  case STATE_YEAR:
    return &map_state_year;

  case STATE_GRAPH:
    return &map_state_graph;

  case STATE_CAL_DAY:
    return &map_state_cal_day;

  case INVALID_STATE:
    break;
  case NUM_STATES:;
    break;
  }

  return &map;
}


void grid_layout(JournalC99 *journalC99)
{
  const float width = (float)GetScreenWidth();
  const float height = (float)GetScreenHeight();
  const float cell_width = width / GRID_COLS;
  const float cell_height = height / GRID_ROWS;
  const Color font_color = GetColor(GuiGetStyle(0, 2));
  const int font_size = (int)(cell_width*0.5F);
  const int font_size_week_day = (int)(font_size/2);
  const int(*map)[SIZE_ROWS][SIZE_COLS] = Return_Map_Pr(journalC99->currentState);

  int i = 1;
  int temp = journalC99->currentState;

  for(int row=0;  row<SIZE_ROWS; row++) {
    for(int col=0; col<SIZE_COLS; col++) {
       const float cell_x =(float) col * cell_width;
       const float cell_y =(float) row * cell_height;
       const Rectangle cell = {cell_x, cell_y, cell_width, cell_height};

       switch ((*map)[row][col]) {
         case TOGGLE_GROUP:
          GuiToggleGroup((Rectangle){cell.x, cell.y, cell.width, cell.height}, "TODAY;MONTH;YEAR;GRAPH", &temp);

          if(temp != journalC99->currentState) { 
            /*
            Event(temp):
            order of EVENT_TABLE (utils.h)  and
            GuiToggleGroup(..., "TODAY;MONTH;YEAR;GRAPH", ...);
            should be the same.
            */
            Update_State(journalC99, (Event)temp);
          }

          break;

      case ELMNT_CAL_DAY:
        if (GuiButton((Rectangle){cell.x, cell.y, cell.width-(cell.width*0.05F),
                       cell.height-(cell_height*0.05F)}, TextFormat("%d", i)))
        {
          snprintf(selected_cal_day_number, sizeof(i), "%u", i);
          journalC99->context.selected_cal_month= current_month_name;
          journalC99->context.selected_cal_day=days_of_week_year_2025[(offset_days_in_month[current_month] - 2 )  + i ];
          journalC99->context.selected_cal_day_number=selected_cal_day_number;
          Update_State(journalC99, evt_btn_cal_day);
        }
        i++;
        break;

      case ELMNT_SUNDAY:
        DrawText("Sun", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;

      case ELMNT_MONDAY:
        DrawText("Mon", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;

      case ELMNT_TUESDAY:
        DrawText("Tue", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;

      case ELMNT_WEDNESDAY:
        DrawText("Wed", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;

      case ELMNT_THURSDAY:
        DrawText("Thu", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;
      case ELMNT_FRIDAY:
        DrawText("Fri", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;
      case ELMNT_SATURDAY:
        DrawText("Sat", (int)cell.x, (int)cell.y, font_size_week_day, font_color);
        break;

      case ELMNT_MONTH:
        DrawText(current_month_name, (int)cell.x, (int)cell.y, font_size, font_color);
        break;

      case ELMNT_TEXT:
        DrawText(current_month_name, (int)cell.x, (int)cell.y, font_size, RAYWHITE);
        break;

      case ELMNT_CURR_DAY_NAME:
        DrawText(current_day_name, (int)cell.x-((int)cell_width/2), (int)cell.y, font_size, font_color);
        break;

      case ELMNT_CURR_DAY_NUMBER:
        DrawText(current_day_number, (int)cell.x+cell_width, (int)cell.y, font_size, font_color);
        break;

      case ELMNT_SELECTED_CAL_MONTH:
        DrawText(journalC99->context.selected_cal_month, (int)cell.x, (int)cell.y, font_size, font_color);
        break;

       case ELMNT_SELECTED_CAL_DAY:
        DrawText(journalC99->context.selected_cal_day, (int)cell.x-(int)cell_width/2, (int)cell.y, font_size, font_color);
        break;

       case ELMNT_SELECTED_CAL_DAY_NUMBER:
        DrawText(journalC99->context.selected_cal_day_number, (int)cell.x+cell_width, (int)cell.y, font_size, font_color);
        break;

      default:
        break;
      }
    }
  }
}

void setup_raylib(void) {
  int screenW = 800;
  int screenH = 600;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenW, screenH, "Journal");
  SetTargetFPS(30);
  GuiLoadStyleCyber();
}



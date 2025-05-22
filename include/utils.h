#ifndef UTILS_H
#define UTILS_H

// if #include "../include/raygui.h" I get ->  "redefinition of guiIcons""
#include <raylib.h>
#include <stdint.h>
#include <sys/time.h>

#define GRID_COLS 12

#define GRID_ROWS 8

#define GRID_PADDING 10.0F
#define CELL_MARGIN 5.0F

#define STATE_TABLE                                                            \
  X(INVALID_STATE)                                                             \
  X(STATE_ROOT_TODAY)                                                          \
  X(STATE_MONTH)                                                               \
  X(STATE_YEAR)                                                                \
  X(STATE_GRAPH)                                                               \
  X(NUM_STATES)

#define EVENT_TABLE                                                            \
  X(evt_btn_today)                                                             \
  X(evt_btn_month)                                                             \
  X(evt_btn_year)                                                              \
  X(evt_btn_graph)                                                             \
  X(NUM_EVENTS)

#define X(state) state,
typedef enum
{
  STATE_TABLE
} State;
#undef X

#define X(event) event,
typedef enum
{
  EVENT_TABLE
} Event;
#undef X

extern char *state_name[];
extern char *event_name[];

extern State transition_table[NUM_STATES][NUM_EVENTS];

typedef struct
{
  State currentState;
  //  struct {
  //   const char* display;
  // } context;
} JournalC99;

#define ELEMENT_LIST                                                           \
  X(ELMNT_BLANK)                                                               \
  X(ELMNT_DAY)                                                                 \
  X(BTN_B)                                                                     \
  X(BTN_C)                                                                     \
  X(TOGGLE_GROUP)                                                              \
  X(ELMNT_LABEL)                                                               \
  X(ELMNT_SUNDAY)                                                              \
  X(ELMNT_MONDAY)                                                              \
  X(ELMNT_TUESDAY)                                                             \
  X(ELMNT_WEDNESDAY)                                                           \
  X(ELMNT_THURSDAY)                                                            \
  X(ELMNT_FRIDAY)                                                              \
  X(ELMNT_SATURDAY)                                                            \
  X(ELMNT_MONTH)                                                               \
  X(ELMNT_NUM)

#define X(element) element,
typedef enum
{
  ELEMENT_LIST
} Element;
#undef X

#define MAX_PROJECTS 4
#define MAX_MONTHS 12
#define MAX_DAYS_IN_MONTH 31
#define MAX_PROJECT_NAME_LEN 64
#define MAX_COMMENT_LEN 256
#define MAX_TIME_STRING_LEN 6
#define SIZE_ROW  12
#define SIZE_COL  12

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
} DaySummary;

typedef struct
{
  char monthName[10];
  DaySummary days[MAX_DAYS_IN_MONTH];
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

extern char *element_list[];
char *current_month_name;
int (*Return_Map_Pr(State state))[12];

// forward declaration to avoid
void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
int GuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode);
int GuiLabel(Rectangle bounds, const char *text);
int GuiButton(Rectangle bounds, const char *text);
void Grid_Layout(JournalC99 *journalC99);
int GuiToggleGroup(Rectangle bounds, const char *text, int *active);
State Update_State(JournalC99 *journalC99, Event event);

#endif

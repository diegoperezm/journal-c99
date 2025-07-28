#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <stdint.h>
#include <sys/time.h>

#define GRID_COLS 12.0f
#define GRID_ROWS 12.0f
#define GRID_PADDING 10.0f
#define GRID_PADDING 10.0f
#define CELL_MARGIN 12.0f

#define MAX_PROJECTS 4
#define MAX_MONTHS 12
#define MAX_DAYS_IN_MONTH 31
#define MAX_PROJECT_NAME_LEN 64
#define MAX_COMMENT_LEN 256
#define MAX_TIME_STRING_LEN 6

#define SIZE_COLS 12
#define SIZE_ROWS 12

#define STATE_TABLE                                                            \
  X(STATE_ROOT_TODAY)                                                          \
  X(STATE_MONTH)                                                               \
  X(STATE_YEAR)                                                                \
  X(STATE_GRAPH)                                                               \
  X(INVALID_STATE)                                                             \
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
  X(ELMNT_CAL_DAY)                                                                 \
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
  X(ELMNT_TEXT)                                                                \
  X(ELMNT_CURR_DAY_NAME)                                                       \
  X(ELMNT_CURR_DAY_NUMBER)                                                     \
  X(ELMNT_NUM)

#define X(element) element,
typedef enum
{
  ELEMENT_LIST
} Element;
#undef X

void setup_raylib(void);
void grid_layout(JournalC99 *journalC99);
extern char *element_list[];
int (*Return_Map_Pr(State state))[SIZE_ROWS][SIZE_COLS];
State Update_State(JournalC99 *journalC99, Event event);
#endif


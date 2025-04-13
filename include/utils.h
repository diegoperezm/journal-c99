#ifndef UTILS_H
#define UTILS_H

// if #include "../include/raygui.h" I get ->  "redefinition of guiIcons""
#include <raylib.h>

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
  X(ELMNT_NUM)

#define X(element) element,
typedef enum
{
  ELEMENT_LIST
} Element;
#undef X

extern char *element_list[];
int (*Return_Map_Pr(State state))[12];

// forward declaration to avoid
int GuiButton(Rectangle bounds, const char *text);
void Grid_Layout(JournalC99 *journalC99);
int GuiToggleGroup(Rectangle bounds, const char *text, int *active);
State Update_State(JournalC99 *journalC99, Event event);

#endif

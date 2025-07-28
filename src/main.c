#include <raylib.h>
#include "../include/utils.h"
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  const Color BGCOLOR = (Color){1,34,43,255};
  JournalC99 journalC99 = { .currentState = STATE_ROOT_TODAY };
  setup_raylib();

  while (!WindowShouldClose()) {

    // Begin
    BeginDrawing();
      ClearBackground(BGCOLOR);
      grid_layout(&journalC99);
    EndDrawing();
    // End
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

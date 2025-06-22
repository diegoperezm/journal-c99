#include "../include/raygui.h"
#include "../include/style_cyber.h"
#include "../include/utils.h"
#include <raylib.h>

int main(void) {

  int screenW = 800;
  int screenH = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenW, screenH, "Journal");
  SetTargetFPS(24);

  GuiLoadStyleCyber();

  JournalC99 journalC99 = { .currentState = STATE_ROOT_TODAY };

  while (!WindowShouldClose()) {

    // Begin
    BeginDrawing();
    ClearBackground(
        GetColor((unsigned int)GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    Grid_Layout(&journalC99);
    EndDrawing();
    // End
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

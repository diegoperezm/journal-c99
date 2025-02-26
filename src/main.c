#include "../include/raygui.h"
#include "../include/utils.h"
#include <raylib.h>

int main(void) {

  int screenW = 800;
  int screenH = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenW, screenH, "Media Player");
  SetTargetFPS(24);

  GuiLoadStyle("../resources/cyber.rgs");

  JournalC99 journalC99 = { .currentState = STATE_WAITING };

  while (!WindowShouldClose()) {

    // Begin
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    // Update(&journalC99);

    GridLayout(&journalC99);
    EndDrawing();
    // End
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

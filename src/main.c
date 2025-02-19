#include "../include/raygui.h"
#include "../include/utils.h"
#include <raylib.h>
// #include <stdio.h>
#define MIN_WIDTH 200
#define MIN_HEIGHT 200

int main(void) {

  int screenW = 800;
  int screenH = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenW, screenH, "Media Player");
  SetTargetFPS(20);

  GuiLoadStyle("../resources/cyber.rgs");

  while (!WindowShouldClose()) {
    // Get updated screen size
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    // Begin
    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    DrawText("Calendario", 350, 50, 20, RAYWHITE);

    GridLayout(width, height);

    EndDrawing();
    // End
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

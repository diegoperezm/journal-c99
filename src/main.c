#include "../include/raygui.h"
#include <raylib.h>
#include <stdio.h>

int main(void) {

  float screenW = 600.0F;
  float screenH = 600.0F;

  InitWindow((int)screenW, (int)screenH, "Media Player");

  Rectangle textBox = { screenW / 2.0F - 100, 180, 225, 50 };

  SetTargetFPS(20);

  while (!WindowShouldClose()) {

    // Begin
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    DrawRectangleRec(textBox, LIGHTGRAY);
    EndDrawing();
    // End
  }

  CloseWindow();
  return EXIT_SUCCESS;

  printf("Hello, world.");
}

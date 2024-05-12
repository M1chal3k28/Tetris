#include <iostream>
#include <raylib.h>

const int screenWidth = 500;
const int screenHeight = 800;

int main(){
    InitWindow(screenWidth, screenHeight, "Tetris 1.0.0");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

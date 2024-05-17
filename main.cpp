#include <Game.hpp>

const int screenWidth = 751;
const int screenHeight = 821;

int main(){
    InitWindow(screenWidth, screenHeight, "Tetris 1.0.0");
    SetTargetFPS(60);

    // Init variables
    srand(time(NULL));
    Game tetris = Game(); 

    while(!WindowShouldClose()) {
        tetris.Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(Color({55, 53, 255, 255}));
        tetris.Draw();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

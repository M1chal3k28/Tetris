#include <Game.hpp>

const int screenWidth = 701;
const int screenHeight = 801;

int main(){
    InitWindow(screenWidth, screenHeight, "Tetris 1.0.0");
    SetTargetFPS(60);

    // Init variables
    srand(time(NULL));
    Game tetris = Game(); 

    while(!WindowShouldClose()) {
        tetris.Update(GetFrameTime());

        BeginDrawing();
        ClearBackground(Color(BLUE));
        tetris.Draw();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

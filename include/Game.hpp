#ifndef GAME_H
#define GAME_H

#include <Grid.hpp>
#include <Blocks.cpp>
#include <Timer.hpp>

#define BLOCK_TIMER .5f

class Game {
private:
    std::vector<Block> blocks;
    Grid grid;
    std::vector<Block> GetAllBlocks();
    void MoveBlockBottom();
    void MoveBlockLeft();
    void MoveBlockRight();
    void AddBlockToTheGrid();
    Block GetRandomBlock();
    Block currentBlock;
    Block nextBlock;

    float timeUntilMove = .5f;

    Timer blockTimer;
    bool canMove;
    
public:
    Game();

    void Draw();
    void Update(float deltaTime);
    void HandleInput();
};

#endif
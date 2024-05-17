#ifndef GAME_H
#define GAME_H

#include <Grid.hpp>
#include <Blocks.cpp>
#include <Timer.hpp>
#include <FontManager.hpp>
#include <Movement.hpp>
#include <State.hpp>
#include <memory> 

#define BLOCK_TIMER .5f
#define RESET_COOLDOWN 1.f
#define MAIN_FONT "MainFont"

class Game {
private:
    std::vector<Block> blocks;
    Grid grid;
    std::vector<Block> GetAllBlocks();
    void HandleInput(float deltaTime);
    void Reset();
    void MoveBlock(const Position direction);
    void MoveBlockBottom();
    void AddBlockToTheGrid();
    Block GetRandomBlock();
    Block currentBlock;
    Block nextBlock;

    float timeUntilMove = .5f;

    Timer deathCooldown;
    Timer blockTimer;
    bool canMove;

    std::shared_ptr<int> score;

    std::shared_ptr<States::State> gameState;

    // Managers
    FontManager fontManager;
    
public:
    Game();

    void Draw();
    void Update(float deltaTime);
};

#endif
#include <Game.hpp>
#include <cstdlib>

Game::Game() 
    : grid(), 
      blocks(this->GetAllBlocks()),
      currentBlock(this->GetRandomBlock()),
      nextBlock(this->GetRandomBlock()),
      blockTimer(),
      canMove(true) {
        blockTimer.StartTimer(BLOCK_TIMER);
      }

void Game::Draw() {
    grid.Draw();
    currentBlock.Draw();
}

void Game::Update(float deltaTime) {
    if(blockTimer.UpdateTimer(deltaTime)) {
        blockTimer.StartTimer(timeUntilMove);

        std::vector<Position> tiles = currentBlock.GetCellPositions();
        bool flag = false;
        for(Position tile: tiles) {
            if((flag = grid.IsCellOutside(tile, 1, 0)))
                break;
        }

        if(flag) {
            // if sent block faster restart timer in proper way
            timeUntilMove = BLOCK_TIMER;
            blockTimer.StartTimer(timeUntilMove);
            canMove = true;
            
            // add block to the grid
            grid.Add(currentBlock.GetCellPositions(), currentBlock.getId());
            currentBlock = nextBlock;
            nextBlock = this->GetRandomBlock();
        } else    
            currentBlock.Move(1, 0);
    }
}

void Game::HandleInput() {
    if(!this->canMove)
        return;

    int keyPressed = GetKeyPressed();

    switch(keyPressed) {
        case KEY_LEFT:{
            this->MoveBlockLeft();
        } break;

        case KEY_RIGHT: {
            this->MoveBlockRight();
        } break;

        case KEY_UP: {
            currentBlock.Rotate();
            std::vector<Position> tiles = currentBlock.GetCellPositions();
            for(Position tile: tiles) {
                if(grid.IsCellOutside(tile)) {
                    currentBlock.UndoRotation();
                    break;
                }
            }
        } break;

        case KEY_DOWN:
            timeUntilMove = 0.01f;
            blockTimer.StartTimer(timeUntilMove);
            canMove = false;
        break;
    }
}

// Private Methods
void Game::MoveBlockLeft() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for(Position tile: tiles) {
        if(grid.IsCellOutside(tile, 0, -1))
            return;
    }
    
    currentBlock.Move(0, -1);
}

void Game::MoveBlockRight() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for(Position tile: tiles) {
        if(grid.IsCellOutside(tile, 0, 1))
            return;
    }
    
    currentBlock.Move(0, 1);
}

Block Game::GetRandomBlock() {
    if(blocks.empty()) 
        blocks = this->GetAllBlocks();

    int randomIndex = rand() % blocks.size();
    Block newBlock = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return newBlock;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}
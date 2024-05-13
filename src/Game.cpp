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
    // If block timer ends move block down
    if(blockTimer.UpdateTimer(deltaTime)) {
        blockTimer.StartTimer(timeUntilMove);

        this->MoveBlockBottom();
    }
}

void Game::AddBlockToTheGrid() {
    // add block to the grid
    grid.Add(this->currentBlock.GetCellPositions(), this->currentBlock.getId());
    this->currentBlock = this->nextBlock;
    this->nextBlock = this->GetRandomBlock();
}

void Game::HandleInput() {
    // if fast falling player can't move
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
            std::vector<Position> tiles = this->currentBlock.GetCellPositions();
            std::cout << "====\nBlock id - " << this->currentBlock.getId() << "\n"; 
            for(auto tile : tiles) {
                std::cout << "Col - " << tile.col << " Row - "<< tile.row << "\n";
            }

            if(!this->grid.RotationSuccess(tiles)) 
                this->currentBlock.UndoRotation();
            
        } break;

        case KEY_DOWN:
            this->timeUntilMove = 0.01f;
            this->blockTimer.StartTimer(timeUntilMove);
            this->canMove = false;
        break;
    }
}

// Private Methods
void Game::MoveBlockBottom() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    MoveTroubles flag = CAN_MOVE;
    for(Position tile: tiles)
        if((flag = grid.IsMovePossible(tile, 1, 0)) != CAN_MOVE)
            break;

    if(flag != CAN_MOVE) {
        // if sent block faster restart timer in proper way
        timeUntilMove = BLOCK_TIMER;
        blockTimer.StartTimer(timeUntilMove);
        canMove = true;

        // Addblock to the grid and change currentBlock to nextBlock
        this->AddBlockToTheGrid();
        return;
    }
    // Move Only when it's possible
    currentBlock.Move(1, 0);
}
void Game::MoveBlockLeft() {
    std::vector<Position> tiles = this->currentBlock.GetCellPositions();

    for(Position tile: tiles) {
        if(grid.IsMovePossible(tile, 0, -1) == BLOCK) {
            AddBlockToTheGrid();
            return;
        }

        if(grid.IsMovePossible(tile, 0, -1) == WALL)
            return;
    }
    
    currentBlock.Move(0, -1);
}

void Game::MoveBlockRight() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for(Position tile: tiles) {
        if(grid.IsMovePossible(tile, 0, 1) == BLOCK) {
            AddBlockToTheGrid();
            return;
        }

        if(grid.IsMovePossible(tile, 0, 1) == WALL)
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
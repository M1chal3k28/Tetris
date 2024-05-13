#include <Game.hpp>
#include <cstdlib>

Game::Game() 
    : grid(), 
      blocks(this->GetAllBlocks()),
      currentBlock(this->GetRandomBlock()),
      nextBlock(this->GetRandomBlock()),
      blockTimer(),
      canMove(true),
      fontManager(),
      gameState(new States::State) {

        // Load Main font
        if(!fontManager.InitializeFont("../res/fonts/Hexenkoetel-qZRv1.ttf", MAIN_FONT))
            exit(1);

        // Set Main Font
        {
            std::shared_ptr<MyFont> font = fontManager.GetFontByName(MAIN_FONT);
            font->setColor(Colors::DarkGray);
            font->setSize(35);
        }

        blockTimer.StartTimer(BLOCK_TIMER);
      }

void Game::Draw() {
    switch(this->gameState->GetState()) {
        // Draw Menu stuff
        case States::Menu : {
            fontManager.GetFontByName(MAIN_FONT)->drawText("Tetris", 100);
            fontManager.GetFontByName(MAIN_FONT)->drawText("Press 'Space' to play !");
        } break;

        // Draw game stuff (for gameover, paused and game there is same stuff)
        case States::GameOver: {
            // Game over Screen
        } case States::Paused:
          case States::Game : {
            grid.Draw();
            currentBlock.Draw();
        } break;
        
    }
}

void Game::Update(float deltaTime) {
    this->HandleInput();
    switch(this->gameState->GetState()) {
        // Update menu stuff
        case States::Menu : {
            
        } break;

        // Update game stuff
        case States::Game : {
            // If block timer ends move block down
            if(blockTimer.UpdateTimer(deltaTime)) {
                blockTimer.StartTimer(timeUntilMove);

                this->MoveBlockBottom();
            }

            // Update grid
            // Grid will check if any line is fulfilled
            grid.Update(this->gameState);
        } break;
    }
}

void Game::AddBlockToTheGrid() {
    // add block to the grid
    grid.Add(this->currentBlock.GetCellPositions(), this->currentBlock.getId());
    this->currentBlock = this->nextBlock;
    this->nextBlock = this->GetRandomBlock();
}

// Private Methods
void Game::HandleInput() {
    int keyPressed = GetKeyPressed();

    switch(this->gameState->GetState()) {
        // Handle input for game
        case States::Game: {
            // if fast falling player can't move
            if(!this->canMove)
                return;
                
            switch(keyPressed) {
                // Move Left
                case KEY_LEFT:{
                    this->MoveBlock(Movement::moveLeft);
                } break;
                
                // Move Right
                case KEY_RIGHT: {
                    this->MoveBlock(Movement::moveRight);
                } break;

                // Rotate clock wisely
                case KEY_UP: {
                    currentBlock.Rotate();
                    std::vector<Position> tiles = this->currentBlock.GetCellPositions();

                    if(!this->grid.RotationSuccess(tiles)) 
                        this->currentBlock.UndoRotation();
                    
                } break;

                // Send block faster
                case KEY_DOWN: {
                    this->timeUntilMove = 0.01f;
                    this->blockTimer.StartTimer(timeUntilMove);
                    this->canMove = false;
                } break;
            }
        } break;

        // Handle input for menu
        case States::Menu: {
            switch(keyPressed) {
                // Start game
                case KEY_SPACE: {
                    this->gameState->SetState(States::Game);
                } break;
            }
        };
    }
}

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

void Game::MoveBlock(const Position direction) {
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for(Position tile: tiles) {
        if(grid.IsMovePossible(tile, direction.row, direction.col) == BLOCK) {
            AddBlockToTheGrid();
            return;
        }

        if(grid.IsMovePossible(tile, direction.row, direction.col) == WALL)
            return;
    }
    
    currentBlock.Move(direction.row, direction.col);
}
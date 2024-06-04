#include <Game.hpp>
#include <cstdlib>
#include <cstring>
#include <string>

Game::Game() 
    : grid(), 
      blocks(this->GetAllBlocks()),
      currentBlock(this->GetRandomBlock()),
      nextBlock(this->GetRandomBlock()),
      blockTimer(),
      deathCooldown(),
      canMove(true),
      fontManager(),
      score(new int(0)),
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
            fontManager.GetFontByName(MAIN_FONT)->drawText("GAME OVER !", 581.5, 600);
        } case States::Paused:
          case States::Game : {
            std::string scoreInString = std::to_string(*this->score);
            char * scoreInText = new char [scoreInString.length()+9];
            std::strcpy (scoreInText, "SCORE: ");
            std::strcat (scoreInText, scoreInString.c_str());

            fontManager.GetFontByName(MAIN_FONT)->drawText(scoreInText, 581.5, 100);
            fontManager.GetFontByName(MAIN_FONT)->drawText("Next:", 581.5, 180);
            DrawRectangleRounded({470, 215, 220, 180}, 0.4f, 4, Color({255, 255, 255, 50}));
            this->nextBlock.DrawNextBlock();
            
            grid.Draw();
            currentBlock.Draw(11, 11);
            switch (nextBlock.getId())
            {
            case 3:
                nextBlock.Draw(380, 285);
                break;

            case 4:
                nextBlock.Draw(380, 265);
                break;
            
            default:
                nextBlock.Draw(400, 260);
                break;
            }
        } break;
        
    }
}

void Game::Update(float deltaTime) {
    this->HandleInput(deltaTime);
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
            grid.Update(this->score);
        } break;
    }
}

void Game::AddBlockToTheGrid() {
    bool DoNotFit = !grid.BlockFits(this->currentBlock.GetCellPositions());

    // add block to the grid
    grid.Add(this->currentBlock.GetCellPositions(), this->currentBlock.getId());
    if(DoNotFit) {
        deathCooldown.StartTimer(RESET_COOLDOWN);
        this->gameState->SetState(States::GameOver);
        return;
    }

    this->currentBlock = this->nextBlock;
    this->nextBlock = this->GetRandomBlock();
}

// Private Methods
void Game::HandleInput(float deltaTime) {
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
        
        case States::GameOver: {
            if(deathCooldown.UpdateTimer(deltaTime) && keyPressed != 0) {
                this->Reset();
                this->gameState->SetState(States::Game);
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

void Game::Reset() {
    grid.Clear();
    this->blocks = this->GetAllBlocks();
    this->currentBlock = this->GetRandomBlock();
    this->nextBlock = this->GetRandomBlock();
    this->blockTimer.StartTimer(BLOCK_TIMER);
    *this->score = 0;
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
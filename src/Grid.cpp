#include <Grid.hpp>

// Public Methods
Grid::Grid() :
    width(10), height(20), cubeSize(40), 
    grid(this->height, std::vector<int>(this->width, 0)), 
    cellColors(Colors::GetCellsColors()) {}
    // Initializing grid and cellColors vector

Grid::~Grid() = default;

void Grid::Draw() {
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            int cellVal = this->grid[row][col];
            // Draw cell
            DrawRectangle(col * this->cubeSize + 1, row * this->cubeSize + 1, this->cubeSize - 1, this->cubeSize - 1, this->cellColors[cellVal]);
        }
    }
}

bool Grid::RotationSuccess(std::vector<Position> tiles ) {
    for(Position tile: tiles) 
        if(IsMovePossible(tile, 0, 0) != CAN_MOVE)
            return false;

    return true;
}

MoveTroubles Grid::IsMovePossible(Position pos, int moveRow, int moveCol) {
    if(this->IsCellOutside(pos, moveRow, moveCol) != CAN_MOVE)
        return WALL;

    if(grid[pos.row + moveRow][pos.col + moveCol] != 0)
        return BLOCK;
    
    return CAN_MOVE;
}

void Grid::Add(std::vector<Position> tiles, int blockId) {
    for(Position tile: tiles) 
        grid[tile.row][tile.col] = blockId;
}

// Private Methods
MoveTroubles Grid::IsCellOutside(Position pos, int moveRow, int moveCol) {
    if(pos.col + moveCol < 0 ||
       pos.col + moveCol >= width ||
       pos.row + moveRow >= height ||
       pos.row + moveRow < 0)
       return WALL;
    return CAN_MOVE;
}

MoveTroubles Grid::IsCellOutside(Position pos)
{
    if(pos.col < 0 ||
       pos.col >= width ||
       pos.row >= height ||
       pos.row < 0)
       return WALL;
    return CAN_MOVE;
}
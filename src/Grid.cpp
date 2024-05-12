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

bool Grid::IsCellOutside(Position pos, int moveRow, int moveCol) {
    if(pos.col + moveCol < 0 ||
       pos.col + moveCol >= width ||
       pos.row + moveRow >= height)
       return true;
    return false;
}

bool Grid::IsCellOutside(Position pos)
{
    if(pos.col < 0 ||
       pos.col >= width ||
       pos.row >= height)
       return true;
    return false;
}

void Grid::Add(std::vector<Position> tiles, int blockId) {
    for(Position tile: tiles) 
        grid[tile.row][tile.col] = blockId;
}

// Private Methods
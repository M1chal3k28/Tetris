#include <Block.hpp>

Block::Block() 
    : cellSize(40),
      cellColors(Colors::GetCellsColors()),
      rotation(0),
      colOffset(0),
      rowOffset(0) {}

Block::~Block() = default;

void Block::Draw() {
    std::vector<Position> tiles = this->GetCellPositions();
    for(Position item: tiles) {
        DrawRectangle(item.col * this->cellSize + 11, item.row * this->cellSize + 11, this->cellSize - 1, this->cellSize - 1, cellColors[this->id]);
    }
}

void Block::Move(int row, int col) {
    rowOffset += row;
    colOffset += col;
}

std::vector<Position> Block::GetCellPositions() {
    std::vector<Position> tiles = cells[rotation];
    std::vector<Position> movedTiles;

    for(Position tile : tiles) {
        Position newPos = Position(tile.row += rowOffset, tile.col += colOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;
}

void Block::Rotate() {
    if(this->rotation < cells.size() - 1)
        rotation++;
    else 
        rotation = 0;
}

void Block::UndoRotation() {
    if(this->rotation != 0)
        rotation--;
    else 
        rotation = cells.size() - 1;
}

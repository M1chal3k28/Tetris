#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <vector>
#include <iostream>
#include <Position.hpp>
#include <Colors.hpp>

class Block
{
protected:
    std::map<int, std::vector<Position>> cells;
    int id;

private:
    int rotation;
    int cellSize;
    std::vector<Color> cellColors;
    int rowOffset;
    int colOffset;
     
public:
    Block();
    ~Block();

    void Draw(int offsetX, int offsetY);
    void DrawNextBlock();
    void Move(int row, int col);
    std::vector<Position> GetCellPositions();
    const int getId() { return this->id; }
    void Rotate();
    void UndoRotation();
};

#endif
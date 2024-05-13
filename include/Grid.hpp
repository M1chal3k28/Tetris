#ifndef GRID_H
#define GRID_H

#include <vector>
#include <raylib.h>
#include <iostream>
#include <Colors.hpp>
#include <Position.hpp>

enum MoveTroubles {
    WALL,
    BLOCK,
    CAN_MOVE
};

class Grid
{
private:
    // Private variables
    const int width, height, cubeSize;
    std::vector<std::vector<int>> grid;
    std::vector<Color> cellColors;
    MoveTroubles IsCellOutside(Position pos, int moveRow, int moveCol);
    MoveTroubles IsCellOutside(Position pos);
    
public:
    Grid();
    ~Grid();

    void Draw();
    bool RotationSuccess(std::vector<Position> tiles);
    MoveTroubles IsMovePossible(Position pos, int moveRow, int moveCol);
    void Add(std::vector<Position> tiles, int blockId);
};

#endif
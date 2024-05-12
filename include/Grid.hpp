#ifndef GRID_H
#define GRID_H

#include <vector>
#include <raylib.h>
#include <iostream>
#include <Colors.hpp>
#include <Position.hpp>

class Grid
{
private:
    // Private variables
    const int width, height, cubeSize;
    std::vector<std::vector<int>> grid;
    std::vector<Color> cellColors;
    
public:
    Grid();
    ~Grid();

    void Draw();
    bool IsCellOutside(Position pos, int moveRow, int moveCol);
    bool IsCellOutside(Position pos);
    void Add(std::vector<Position> tiles, int blockId);
};

#endif
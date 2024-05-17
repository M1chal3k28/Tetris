#include <Colors.hpp>

const Color Colors::DarkGray = {26, 31, 40, 255};
const Color Colors::Blue = {0, 128, 255, 255};      // I-tetrimino (cyan)
const Color Colors::Red = {255, 64, 64, 255};       // Z-tetrimino (red)
const Color Colors::Yellow = {255, 255, 128, 255};  // O-tetrimino (yellow)
const Color Colors::Green = {64, 255, 64, 255};     // S-tetrimino (green)
const Color Colors::Purple = {191, 64, 191, 255};   // T-tetrimino (purple)
const Color Colors::Orange = {255, 200, 128, 255};  // L-tetrimino (orange)
const Color Colors::Cyan = {128, 255, 255, 255};    // J-tetrimino (blue)

std::vector<Color> Colors::GetCellsColors() 
    {return {Colors::DarkGray, 
             Colors::Green, 
             Colors::Red, 
             Colors::Orange, 
             Colors::Yellow, 
             Colors::Purple, 
             Colors::Cyan, 
             Colors::Blue};}
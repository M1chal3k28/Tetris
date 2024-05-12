#include <Colors.hpp>

const Color Colors::DarkGray = {26, 31, 40, 255};
const Color Colors::Blue = {0, 0, 255, 255};
const Color Colors::Red = {255, 0, 0, 255};
const Color Colors::Yellow = {255, 255, 0, 255};
const Color Colors::Green = {0, 255, 0, 255};
const Color Colors::Purple = {128, 0, 128, 255};
const Color Colors::Orange = {255, 165, 0, 255};
const Color Colors::Cyan = {0, 255, 255, 255};

std::vector<Color> Colors::GetCellsColors() 
    {return {Colors::DarkGray, 
             Colors::Green, 
             Colors::Red, 
             Colors::Orange, 
             Colors::Yellow, 
             Colors::Purple, 
             Colors::Cyan, 
             Colors::Blue};}
#ifndef COLORS_H
#define COLORS_H

#include <raylib.h>
#include <vector>

namespace Colors
{
    extern const Color DarkGray;
    extern const Color Green;
    extern const Color Red; 
    extern const Color Orange; 
    extern const Color Yellow; 
    extern const Color Purple; 
    extern const Color Cyan; 
    extern const Color Blue;

    std::vector<Color> GetCellsColors();
} // namespace Colors


#endif
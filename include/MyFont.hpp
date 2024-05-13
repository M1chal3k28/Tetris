#ifndef MYFONT_H
#define MYFONT_H

#include <memory>
#include <raylib.h>

class MyFont {
private:
    std::unique_ptr<Font> font;
    Vector2 position;
    int size;
    int spacing;
    Color color;

    void setPosition(int x, int y);
    void placeInTheCenterX(const char *text);
    void placeInTheCenter(const char *text);

public:
    MyFont(std::unique_ptr<Font> font);

    void setSize(int size);
    void setColor(Color color);

    void drawText(const char* text);
    void drawText(const char *text, int x, int y);
    void drawText(const char *text, int y);
};

#endif
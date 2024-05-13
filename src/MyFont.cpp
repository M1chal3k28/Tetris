#include "MyFont.hpp"

// Create font object easy to configure
MyFont::MyFont(std::unique_ptr<Font> font)
 : font(std::move(font)), position(), size(0), spacing(5), color(BLACK) {
    position.x = 0;
    position.y = 0;
 }

void MyFont::setSize(int size) {
    this->size = size;
}

void MyFont::setColor(Color color) {
    this->color = color;
}

// Draw text in the center
void MyFont::drawText(const char* text) {
    this->placeInTheCenter(text);
    DrawTextEx(*this->font, text, this->position, this->size, this->spacing, this->color);
}

// Draw text in given position
void MyFont::drawText(const char* text, int x, int y) {
    this->setPosition(x, y);
    DrawTextEx(*this->font, text, this->position, this->size, this->spacing, this->color);
}

// Draw in center on Xs and given Y
void MyFont::drawText(const char* text, int y) {
    this->placeInTheCenterX(text);
    this->position.y = y;

    DrawTextEx(*this->font, text, this->position, this->size, this->spacing, this->color);
}

// Private methods
void MyFont::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

void MyFont::placeInTheCenterX(const char * text) {
    float measuredPos = MeasureTextEx(*this->font, text, this->size, this->spacing).x;
    this->position.x = GetScreenWidth() / 2 - measuredPos/ 2;
}

void MyFont::placeInTheCenter(const char * text) {
    Vector2 measuredPos = MeasureTextEx(*this->font, text, this->size, this->spacing);
    this->position.y = GetScreenHeight() / 2 - measuredPos.y / 2;
    this->position.x = GetScreenWidth() / 2 - measuredPos.x / 2;
}
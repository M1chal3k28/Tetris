#include "FontManager.hpp"

FontManager::FontManager() : fonts() {}

bool FontManager::InitializeFont(const char *dir, const std::string fontName)
{
    if(fonts.find(fontName) != fonts.end()) {
        std::cerr << "Can't initialize font with name " << fontName << " | Font exists";
        return false;
    }

    if(FileExists(dir))
        fonts.insert(std::make_pair(fontName, new MyFont( std::make_unique<Font>( Font( LoadFont( dir ) ) ) ) )); // Pushing new font with name id !
    else {
        std::cerr << "Can't initialize font with name " << fontName << " | Can't find font"; 
        return false;
    }

    return true;
}

std::shared_ptr<MyFont> FontManager::GetFontByName(const std::string name) {
    if(fonts.find(name) != fonts.end())
        return fonts[name];

    return nullptr;
}
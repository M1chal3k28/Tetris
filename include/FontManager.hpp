#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <memory>
#include <ResourceManager.hpp>
#include <MyFont.hpp>


class FontManager : public ResourceManager {
private:
    std::map<std::string, std::shared_ptr<MyFont>> fonts;

public:
    FontManager();

    bool InitializeFont(const char *dir, const std::string fontName);
    std::shared_ptr<MyFont> GetFontByName(const std::string name);
};

#endif
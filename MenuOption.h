#pragma once
#include <string>
#include "structs.h"

class MenuOption{
public:
    MenuOption();
    MenuOption(int, int, std::string, unsigned char);
    void SetPosition(int, int);
    void SetPosition(Vector2);
    void SetSelected(bool);
    void SetName(const std::string&);
    void SetSubMenu(unsigned char);
    unsigned char GetSubMenu();
    const std::string& GetName();
    void Draw(const unsigned char&);
private:
    unsigned char subMenu;
    std::string name;
    Vector2 position;
    bool selected;
};
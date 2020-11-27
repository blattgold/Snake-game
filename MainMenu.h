#pragma once
#include <vector>
#include "MenuOption.h"

class MainMenu{
public:
    MainMenu();
    void InitOptions();
    unsigned char CheckInput();
    void Draw();
    unsigned char GetSubMenu();
    unsigned char GetSelection();
    ~MainMenu();
private:
    unsigned char subMenu;
    unsigned char selection;
    std::vector<MenuOption*> menuOptionVector;
};
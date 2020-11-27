#include "MenuOption.h"
#include <ncurses.h>

MenuOption::MenuOption(){
    position.x = 0;
    position.y = 0;
    this->name = "unnamed option";
    selected = false;
    this->subMenu = 0;
}
MenuOption::MenuOption(int x, int y, std::string name, unsigned char subMenu){
    position.x = x;
    position.y = y;
    this->name = name;
    selected = false;
    this->subMenu = subMenu;
}
void MenuOption::SetPosition(int x, int y){
    position.x = x;
    position.y = y;
}
void MenuOption::SetPosition(Vector2 position){
    this->position = position;
}
void MenuOption::SetSelected(bool selected){
    this->selected = selected;
}
void MenuOption::SetName(const std::string& name){
    this->name = name;
}
void MenuOption::SetSubMenu(unsigned char subMenu){
    this->subMenu = subMenu;
}
unsigned char MenuOption::GetSubMenu(){
    return subMenu;
}
const std::string& MenuOption::GetName(){
    return name;
}
void MenuOption::Draw(const unsigned char& subMenu){
    if(selected)
        attron(A_UNDERLINE);
    mvprintw(position.y, position.x, name.c_str());
    attroff(A_UNDERLINE);
}
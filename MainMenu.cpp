#include <ncurses.h>
#include "MainMenu.h"
#include "MenuOption.h"

MainMenu::MainMenu(){
    InitOptions();
}
void MainMenu::InitOptions(){
    selection = 0;
    subMenu = 0;
    menuOptionVector.push_back(new MenuOption(1,4,"play", 0));
    menuOptionVector.push_back(new MenuOption(1,5,"quit", 0));
    menuOptionVector.push_back(new MenuOption(6,4,"easy", 1));
    menuOptionVector.push_back(new MenuOption(6,5,"medium", 1));
    menuOptionVector.push_back(new MenuOption(6,6,"hard", 1));
    menuOptionVector.push_back(new MenuOption(6,7,"back", 1));
    menuOptionVector.at(0)->SetSelected(true);
}
unsigned char MainMenu::CheckInput(){
    char ch = getch();
    switch(ch){
    case 'w':
        if (selection == 0 || subMenu == 1 && selection == 2)
            break;
        --selection;
        menuOptionVector.at(selection)->SetSelected(true);
        menuOptionVector.at(selection+1)->SetSelected(false);
        return 1;
    case 's':
        if (selection >= menuOptionVector.size()-1 || selection >= 1 && subMenu == 0)
            break;
        ++selection;
        menuOptionVector.at(selection)->SetSelected(true);
        menuOptionVector.at(selection-1)->SetSelected(false);
        return 1;
    case 'e':
        switch(selection){
        case 0:
            subMenu = 1;
            selection = 2;
            menuOptionVector.at(selection)->SetSelected(true);
            return 1;
        case 1:
            return 0;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            menuOptionVector.at(selection)->SetSelected(false);
            subMenu = 0;
            selection = 0;
            menuOptionVector.at(selection)->SetSelected(true);
            return 1;
        }
        return 1;
    }
    return 1;
}
void MainMenu::Draw(){
    attron(A_UNDERLINE);
    mvprintw(1,1,"MENU");
    attroff(A_UNDERLINE);
    mvprintw(2,1,"press 'e' to select");
    for (int i = 0 ; i < menuOptionVector.size() ; i++)
        if (menuOptionVector.at(i)->GetSubMenu() <= subMenu)
            menuOptionVector.at(i)->Draw(subMenu);
}
unsigned char MainMenu::GetSubMenu(){
    return subMenu;
}
unsigned char MainMenu::GetSelection(){
    return selection;
}
MainMenu::~MainMenu(){
    for (int i = 0 ; i < menuOptionVector.size() ; i++)
        delete menuOptionVector.at(i);
}
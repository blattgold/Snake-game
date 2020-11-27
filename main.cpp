
#include "structs.h"
#include "Game.h"
#include <ncurses.h>

int main(){
    Game game;
    game.SetDebug(false);
    game.GameLoop();

    endwin();
    return 0;
}
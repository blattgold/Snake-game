#include "Game.h"

#include <ncurses.h>
#include <chrono>
#include <thread>

Game::Game(){
    SetMapSize(20, 20);
    Init();
}
Game::Game(int x, int y){
    SetMapSize(x, y);
    Init();
}
Game::Game(Vector2 size){
    SetMapSize(size.x, size.y);
    Init();
}
void Game::Init(){
    initscr();
    raw();
    timeout(5);
    noecho();
    curs_set(0);
    srand (time(NULL));
    playing = false;
    SetDebug(false);
    SetFps(12);
}
void Game::Draw(){
    if (debug == true){
            attron(A_UNDERLINE);
            mvprintw(0, 22, "DEBUG INFO");
            attroff(A_UNDERLINE);
            mvprintw(1, 22, "Target FPS: %d    ", fps);
            mvprintw(2, 22, "Map X: %d Y: %d    ", mapSize.x, mapSize.y);
            mvprintw(3, 22, "Head X: %d Y: %d    ", player.GetPosition().x, player.GetPosition().y);
            mvprintw(4, 22, "Playing: %d    ", playing);
            mvprintw(5, 22, "GameOver: %d     ", player.CheckGameOver());
            mvprintw(6, 22, "Fruit X: %d Y: %d     ", player.GetFruitPosition().x, player.GetFruitPosition().y);
            mvprintw(7, 22, "Menu Selection: %d     ", mainMenu.GetSelection());
            mvprintw(8, 22, "Menu SubMenu: %d     ", mainMenu.GetSubMenu());
        }
    if (playing){
        for ( int i = 0 ; i <= mapSize.x+1 ; i++ ){
            for ( int j = 0 ; j <= mapSize.y+1 ; j++ ){
                if ( i == 0 || i == mapSize.x && j <= mapSize.y){
                    mvaddch(j, i, '#');
                }
                else if ( j == 0 && i <= mapSize.x || j == mapSize.y && i <= mapSize.x){
                    mvaddch(j, i, '#');
                }
                else
                    mvaddch(j, i, ' ');
            }
        }
        player.Draw();
        if (player.CheckGameOver()){
            mvprintw(10,6, "GAME OVER");
            mvprintw(11,2, "press 'q' to quit");
            mvprintw(12,2, "'m' to go to menu");
            mvprintw(13,2, "'r' to restart");
        }

        mvprintw(22, 0, "Press 'i' for info");
    }
    else{
        mainMenu.Draw();
    }
    refresh();
}
void Game::SetMapSize(int x, int y){
    mapSize.x = x;
    mapSize.y = y;
}
void Game::SetDebug(bool debug){
    this->debug = debug;
}
bool Game::GetDebug(){
    return debug;
}
void Game::SetFps(unsigned char fps){
    this->fps = fps;
}
Vector2 Game::GetMapSize(){
    return mapSize;
}
void Game::GameLoop(){
    using clock = std::chrono::steady_clock;
    auto nextFrame = clock::now();
    bool quit = false;
    while(!player.CheckGameOver() && !quit){
        quit = false;
        nextFrame += std::chrono::milliseconds(1000 / fps);

        if(playing && !player.CheckGameOver()){
            if(player.CheckInput() == 1){
                SetDebug(!GetDebug());
                erase();
            }
            player.Move();
            player.CheckCollision();
        }
        else{
            unsigned char ch = mainMenu.CheckInput();
            if(ch == 0)
                break;
            switch(ch){
            case 1:         //do nothing
                break;
            case 2:         //easy
                SetFps(6);
                playing = true;
                break;
            case 3:         //medium
                SetFps(9);
                playing = true;
                break;
            case 4:         //hard
                SetFps(12);
                playing = true;
                break;
            }
        }
        Draw();
        while(player.CheckGameOver() && !quit){
            char ch = getch();
            if (ch == 'q'){
                quit = true;
            }
            else if (ch == 'm'){
                erase();
                playing = false;
                player.Reset();
                nextFrame = clock::now();
            }
            else if (ch =='r'){
                player.Reset();
                nextFrame = clock::now();
            }
        }

        std::this_thread::sleep_until(nextFrame);
    }
}
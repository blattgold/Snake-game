#pragma once
#include "structs.h"
#include "Player.h"
#include "MainMenu.h"

class Game{
public:
    Game();
    Game(int, int);
    Game(Vector2);
    void Init();
    void Draw();
    void SetMapSize(int, int);
    void SetDebug(bool);
    bool GetDebug();
    void SetFps(unsigned char);
    Vector2 GetMapSize();
    void GameLoop();
private:
    bool debug;
    bool playing;
    unsigned char fps;
    Vector2 mapSize;
    Player player;
    MainMenu mainMenu;
};
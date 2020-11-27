#pragma once
#include "PlayerSegment.h"
#include <vector>

class Player{
public:
    Player();
    Vector2 GetPosition();
    void Move();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void AddSegment();
    void UpdateSegments();
    void Reset();
    std::vector<PlayerSegment*> GetSegmentVector();
    Vector2 GetFruitPosition();
    void GotFruit();
    void RespawnFruit();
    void Draw();
    void CheckCollision();
    unsigned char CheckInput();
    bool CheckGameOver();
private:
    Vector2 position;
    Vector2 prevPosition;
    Vector2 fruitPosition;
    int score;
    bool gameOver;
    std::vector<PlayerSegment*> segmentVector;
    unsigned char movedir;
    enum{
        DIR_STOP, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
    };
};
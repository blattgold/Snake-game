#pragma once
#include "structs.h"

class PlayerSegment{
public:
    PlayerSegment();
    void SetPosition(Vector2);
    Vector2 GetPosition();
    Vector2 GetPrevPosition();
private:
    Vector2 position;
    Vector2 prevPosition;
};
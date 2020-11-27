#include "PlayerSegment.h"

PlayerSegment::PlayerSegment(){
    position.x = 0;
    position.y = 0;
    prevPosition = position;
}
Vector2 PlayerSegment::GetPosition(){
    return position;
}
Vector2 PlayerSegment::GetPrevPosition(){
    return prevPosition;
}
void PlayerSegment::SetPosition(Vector2 input){
    prevPosition = position;
    position = input;
}
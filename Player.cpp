#include <ncurses.h>
#include <stdlib.h>

#include "Player.h"

Player::Player(){
    position.x = 10;
    position.y = 10;
    prevPosition.x = 10;
    prevPosition.y = 10;
    RespawnFruit();
    score = 0;
    gameOver = false;
}
Vector2 Player::GetPosition(){
    return position;
}
void Player::Move(){
    switch(movedir){
    case DIR_STOP:
        break;
    case DIR_UP:
        MoveUp();
        break;
    case DIR_DOWN:
        MoveDown();
        break;
    case DIR_LEFT:
        MoveLeft();
        break;
    case DIR_RIGHT:
        MoveRight();
        break;
    default:
        break;
    }
}
void Player::MoveUp(){
    prevPosition = position;
    --position.y;
}
void Player::MoveDown(){
    prevPosition = position;
    ++position.y;
}
void Player::MoveLeft(){
    prevPosition = position;
    --position.x;
}
void Player::MoveRight(){
    prevPosition = position;
    ++position.x;
}
void Player::AddSegment(){
    segmentVector.push_back(new PlayerSegment);
}
void Player::UpdateSegments(){
    if(segmentVector.size() == 0){
        return;
    }
    else{
        segmentVector.at(0)->SetPosition(prevPosition);
        for ( int i = 1 ; i < segmentVector.size() ; i++){
            segmentVector.at(i)->SetPosition(segmentVector.at(i-1)->GetPrevPosition());
        }
    }
}
void Player::Reset(){
    position.x = 10;
    position.y = 10;
    prevPosition.x = 10;
    prevPosition.y = 10;
    score = 0;
    movedir = DIR_STOP;
    gameOver = false;
    RespawnFruit();
    segmentVector.clear();
}
std::vector<PlayerSegment*> Player::GetSegmentVector(){
    return segmentVector;
}
Vector2 Player::GetFruitPosition(){
    return fruitPosition;
}
void Player::GotFruit(){
    ++score;
    AddSegment();
    RespawnFruit();
}
void Player::RespawnFruit(){
    fruitPosition.x = (rand() % 18) + 1;
    fruitPosition.y = (rand() % 18) + 1;
}
void Player::Draw(){
    mvaddch(fruitPosition.y, fruitPosition.x, '*');
    for ( int i = 0 ; i < segmentVector.size() ; i++ ){
        mvaddch(segmentVector.at(i)->GetPosition().y, segmentVector.at(i)->GetPosition().x, 'o');
    }
    mvaddch(position.y, position.x, 'O');
    mvprintw(21, 0, "Score= %d    ", score);
}
void Player::CheckCollision(){
    if(position.x >= 20 || position.x <= 0 || position.y >= 20 || position.y <= 0)
        gameOver = true;
    for (int i = 0 ; i < segmentVector.size() ; i++){
        if (position.x == segmentVector.at(i)->GetPosition().x && position.y == segmentVector.at(i)->GetPosition().y)
            gameOver = true;
    }
    if(position.x == fruitPosition.x && position.y == fruitPosition.y){
        GotFruit();
    }
    UpdateSegments();
}

unsigned char Player::CheckInput(){
    char ch = getch();
    switch(ch){
    case 'w':
        if (movedir == DIR_DOWN && segmentVector.size() > 0)
            break;
        movedir = DIR_UP;
        break;
    case 's':
        if (movedir == DIR_UP && segmentVector.size() > 0)
            break;
        movedir = DIR_DOWN;
        break;
    case 'a':
        if (movedir == DIR_RIGHT && segmentVector.size() > 0)
            break;
        movedir = DIR_LEFT;
        break;
    case 'd':
        if (movedir == DIR_LEFT && segmentVector.size() > 0)
            break;
        movedir = DIR_RIGHT;
        break;
    case 'i':
        return 1;
    }
    return 0;
}

bool Player::CheckGameOver(){
    return gameOver;
}
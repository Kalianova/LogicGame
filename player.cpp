#include "player.h"


Player::Player(int Row, int Colum, int Rotation)
    :row_(Row), colum_ (Colum), rotation_(Rotation)
{
    rowNow = row_;
    columNow = colum_;
    rotationNow = rotation_;
}

void Player::setBeginPosition(int Row, int Colum) {
    row_ = Row;
    colum_ = Colum;
}

void Player::setPosition(int Row, int Colum) {
    rowNow = Row;
    columNow = Colum;
}
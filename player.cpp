#include "player.h"


Player::Player(int Row, int Colum, int Rotation)
    :row_(Row), colum_ (Colum), rotation_(Rotation)
{
    rowNow = row_;
    columNow = colum_;
    rotationNow = rotation_;
}

void Player::setBeginPosition(int Row, int Colum){
    row_ = Row;
    colum_ = Colum;
}

void Player::setPosition(int Row, int Colum) {
	rowNow = Row;
	columNow = Colum;
}

int Player::changeRotation(int Rotation)
{
    rotationNow  = Rotation;
	return 1;
}

/*bool Player::isMoveForward(Map map){
    switch(rotationNow){
    case 0:
        if (rowNow!=0){
            if(map.getNumber(rowNow - 1, columNow)!=0){
                rowNow--;
                return true;
            }
        }
        break;
    case 90:
        if (columNow!=0){
            if(map.getNumber(rowNow, columNow - 1)!=0){
                columNow--;
                return true;
            }
        }
        break;
    case 180:
        if (rowNow!=map.getSize() - 1){
            if(map.getNumber(rowNow + 1, columNow)!=0){
                rowNow--;
                return true;
            }
        }
        break;
    case 270:
        if (columNow!=map.getSize() - 1){
            if(map.getNumber(rowNow, columNow + 1)!=0){
                columNow--;
                return true;
            }
        }
        break;
    default:
        throw std::invalid_argument("Wrong rotation");
    }
    return false;
}*/



/*void Player::slotGameTimer()
{

}*/




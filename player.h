#ifndef PLAYER_H
#define PLAYER_H
#include<QObject>
#include<QGraphicsItem>
//#include<map.h>

class Player
{
public:
    Player() = default;
    Player(int Row, int Colum, int Rotation);
    void setPosition(int Row, int Colum);
    void setBeginPosition(int Row, int Colum);
    int getRow(){
        return rowNow;
    }
    int getColum(){
        return columNow;
    }
    int getRotation() {
        return rotationNow;
    }
    int getBeginRow() {
        return row_;
    }
    int getBeginColum() {
        return colum_;
    }
    int getBeginRotation(){
        return rotation_;
    }
    void moveRight(){rotationNow = (rotationNow+90) % 360;}
    void moveLeft(){rotationNow = (rotationNow + 270) % 360;}

private:
    int row_{0};
    int rowNow{0};
    int columNow{0};
    int colum_{0};
    int rotation_{0};
    int rotationNow{0};
};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H
#include<QObject>
#include<QGraphicsItem>

/**
* @brief Класс для характеристик ракеты
*/
class Player
{
public:
    Player() = default;
    Player(int Row, int Colum, int Rotation);

    /**
* @brief Изменение положения ракеты
*/
    void setPosition(int Row, int Colum);

    /**
* @brief Установка начального положения ракеты
*/
    void setBeginPosition(int Row, int Colum);

    /**
* @brief Получение ряда ракеты сейчас
*/
    int getRow() { return rowNow; }

    /**
* @brief Получение колонки ракеты сейчас
*/
    int getColum() { return columNow; }

    /**
* @brief Получение направления ракеты сейчас
*/
    int getRotation() { return rotationNow; }

    /**
* @brief Получение начального радя ракеты
*/
    int getBeginRow() { return row_; }

    /**
* @brief Получение начальной колонки ракеты
*/
    int getBeginColum() { return colum_; }

    /**
* @brief Получение начального направления ракеты
*/
    int getBeginRotation() { return rotation_; }

    /**
* @brief Поворот ракеты вправо
*/
    void moveRight() { rotationNow = (rotationNow + 90) % 360; }

    /**
* @brief Поворот ракеты влево
*/
    void moveLeft() { rotationNow = (rotationNow + 270) % 360; }

private:
    /**
* @brief Изначальный ряд ракеты
*/
    int row_{ 0 };

    /**
* @brief Ряд, в котором ракета сейчас
*/
    int rowNow{ 0 };

    /**
* @brief Изначальная колонка ракеты
*/
    int columNow{ 0 };

    /**
* @brief Колонка в которой ракета сейчас
*/
    int colum_{ 0 };

    /**
* @brief Изначальное направление ракеты
*/
    int rotation_{ 0 };

    /**
* @brief Напрвление ракеты сейчас
*/
    int rotationNow{ 0 };
};

#endif // PLAYER_H

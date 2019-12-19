#ifndef MAP_H
#define MAP_H


#include<QColor>
#include<vector>
#include<player.h>

/**
* @brief Класс для обозначания карты уровня
*/
class Map{
public:
    Map() = default;
    /**
* @brief Считывание уровня с файла
*/
    void ReadFrom(QString Path);

    /**
* @brief Цвет квадрата
*/
    QColor ColorOfRect(int Height, int Width);
    ~Map() {};
    /**
* @brief Считана ли карта верно
*/
    bool isValid() { return valid; }

    /**
* @brief Значение клетки в карте
*/
    int getNumber(int Height, int Width);

    /**
* @brief Размер карты
*/
    int getSize();

    /**
* @brief Количество функций
*/
    int getFunctionsCount(){return functions.size();}

    /**
* @brief Количество команд
*/
    int getCommandsCount(){return comands.size();}

    /**
* @brief Значение команды
*/
    int getCommand(unsigned int num){return comands[num];}

    /**
* @brief Значение функции
*/
    int getFunction(unsigned int num){return functions[num];}

    /**
* @brief Количество цветов
*/
    int getColorsCount(){return colors.size();}

    /**
* @brief Изменение цвета
*/
    void setColor(int row, int colum, std::string color) {
        TileMap[row].replace(colum, 1, color);
    }

    /**
* @brief Значение цвета
*/
    QColor getColor(unsigned int num){return colors[num];}

    /**
* @brief Ракета
*/
    Player player;
private:
    /**
* @brief Карта
*/
    std::vector<std::string> TileMap;

    /**
* @brief Команды уровня
*/
    std::vector<int> comands;

    /**
* @brief Цвета уровня
*/
    std::vector<QColor> colors;

    /**
* @brief Функции уровня
*/
    std::vector<int> functions;

    /**
* @brief Верно ли считывание карты

*/
    bool valid{ true };
    /**
* @brief Количество звезд в карте
*/
    int countStars{0};
};

#endif // MAP_H

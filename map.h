#ifndef MAP_H
#define MAP_H


#include<QColor>
#include<vector>
#include<player.h>


class Map{
public:
    Map() = default;

    void ReadFrom(QString Path);
    QColor ColorOfRect(int Height, int Width);
    ~Map(){

    }
    bool isValid(){
        return valid;
    }
    int getNumber(int Height, int Width);
    int getSize();
    int getFunctionsCount(){return functions.size();}
    int getCommandsCount(){return comands.size();}
    int getCommand(unsigned int num){return comands[num];}
    int getFunction(unsigned int num){return functions[num];}
    int getColorsCount(){return colors.size();}
    void setColor(int row, int colum, std::string color) {
        TileMap[row].replace(colum, 1, color);
    }
    QColor getColor(unsigned int num){return colors[num];}
    Player player;
private:

    std::vector<std::string> TileMap;
    std::vector<int> comands;
    std::vector<QColor> colors;
    std::vector<int> functions;

    bool valid{ true };
    int countStars{0};
};

#endif // MAP_H

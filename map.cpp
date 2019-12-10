#include <map.h>
#include <fstream>
#include <QFile>
#include <sstream>
#include <QTextStream>

//Считывание карты с файла:
//В первой строке Размер карты [size]
//Далее в каждой строке по [size] символов
//Всего этих строк [size]

//Считывание персонажей:
//После карты числа с положением персонажа (hight, width) и его тип

//Считывание контрольных точек:
//Происхдит вместе со считыванием карты
//Если число >=5 то там контрольная точка
//Количество точек после размера карты в той же строчке

//Считывание команд:
//Их количество, далее их значения на новой строке
//Считывание функций:
//Их количество, далее количества клеточек и последняя цифра номер функции
//Считывание цветов:
//Их количество, далее их значения на новой строке
void Map::ReadFrom(QString Path){
	QFile file(Path);
	file.open(QIODevice::ReadOnly);
    int Size;
	QTextStream stream(&file);
	stream >> Size;
	stream.readLine();
	TileMap.clear();
    for(int i = 0; i<Size;i++){
      TileMap.push_back(stream.readLine().toStdString());
    }
    if(TileMap.size()!=0){
    int row, colum, rotation;
    stream>>row>>colum>>rotation;
    if(ColorOfRect(row,colum)==Qt::black){
		valid = false;
    }
    player = Player(row, colum, rotation);
	stream.readLine();
    stream>>Size;
	stream.readLine();
	if (comands.size() != Size) {
		for (int i = 0; i < Size; i++) {
			int command;
			stream >> command;
			comands.push_back(command);
		}
	}
	stream.readLine();
	stream >> Size;
	stream.readLine();
	if (functions.size() != Size) {
		for (int i = 0; i < Size; i++) {
			int function;
			stream >> function;
			functions.push_back(function);
		}
	}
	stream.readLine();
	stream >> Size;
	stream.readLine();
	if (colors.size() != Size) {
		for (int i = 0; i < Size; i++) {
			int color;
			stream >> color;
			QColor Color;
			switch (color) {
			case 1:
				Color = Qt::blue;
				break;
			case 2:
				Color = Qt::darkMagenta;
				break;
			case 3:
				Color = Qt::red;
				break;
			case 4:
				Color = Qt::darkYellow;
				break;
			default:
				valid = false;
			}
			colors.push_back(Color);
		}
	}
	stream.readLine();
    }
    else{
        valid = false;
    }
	file.close();
}

QColor Map::ColorOfRect(int Height, int Width){
    std::string str = TileMap[Height];

    int num = str[Width] - '0';
    switch(num % 5){
    case 0:
        return Qt::black;
    case 1:
        return Qt::blue;
    case 2:
        return Qt::darkMagenta;
    case 3:
        return Qt::red;
    case 4:
        return Qt::darkYellow;
    default:
        throw std::invalid_argument("Wrong integer for color");
    }
}



int Map::getNumber(int Height, int Width) {
    std::string str = TileMap[Height];
    return str[Width] - '0';
}

int Map::getSize(){
    return TileMap.size();
}

void Map::Draw(){

}

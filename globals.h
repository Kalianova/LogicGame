#ifndef GLOBALS_H
#define GLOBALS_H

#include <exception>

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QColor>

const static int SIZE_OF_MAP = 1000;
const static int SIZE_OF_FUNCTIONS = 5;

class globals
{

public:
    globals();
	QString getPath();
	/*int getSizeOfCreateMap(){
		return sizeOfCreateMap;
	}
	void setSizeOfCreateMap(int size) {
		sizeOfCreateMap = size;
	}*/
	void setPath();
private:
    std::string level;
	QString path;
	//int sizeOfCreateMap;
};

#endif // GLOBALS_H

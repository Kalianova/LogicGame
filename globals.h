#ifndef GLOBALS_H
#define GLOBALS_H

#include <exception>

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QColor>
#include <QString>
#include <QDir>

const static int SIZE_OF_MAP = 1000;
const static int SIZE_OF_FUNCTIONS = 10;


class globals
{

public:
    globals();
private:
    QString level;
	//QDir* dir;
	//QString path{ dir.currentPath() };
};

#endif // GLOBALS_H

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
const static int SIZE_OF_LEVELS = 10;
const static int SIZE_OF_COMMANDS = 12;


class globals
{

public:
    globals();
    void setLevelDone(QString path);
    QString goToLevel();
private:

};

#endif // GLOBALS_H

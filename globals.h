#ifndef GLOBALS_H
#define GLOBALS_H

#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QDir>

const static int SIZE_OF_MAP = 1000;
const static int SIZE_OF_FUNCTIONS = 10;
const static int SIZE_OF_LEVELS = 10;
const static int SIZE_OF_COMMANDS = 12;


class globals
{
public:
    globals(){};
    static void setLevelDone(QString path);
    static QString goToLevel();
    static QString nameOfLevelFromPath(QString path);
};

#endif // GLOBALS_H

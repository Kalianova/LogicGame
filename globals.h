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

/**
* @brief Класс используемый для глобальных методов и значений
*/
class globals
{
public:
    globals() {};


    /**
    * @brief Записывает в файл с адресами всех уровней, значение что уровень был пройден
    */
    static void setLevelDone(QString path);

    /**
    * @brief Определяет следующий уровень, который не был пройден и значения в файле могут быть представлены в виде карты игры
    */
    static QString goToLevel();

    /**
    * @brief Возвращает имя уровня из полного пути к уровню
    */
    static QString nameOfLevelFromPath(QString path);
};

#endif // GLOBALS_H

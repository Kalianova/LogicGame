#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QGraphicsView>
#include<QGraphicsScene>
#include <QGraphicsRectItem>
#include <QtGui>
#include <QtCore>
#include <QShortcut>
#include <QTransform>
#include <QGraphicsItem>
#include"map.h"
#include"click.h"
#include<vector>
#include"globals.h"


namespace Ui {
class GameWindow;
}

/**
* @brief Класс используемый для создания и управления окном игры
*/
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QString, QWidget* parent = nullptr);
    ~GameWindow() override;

    /**
* @brief Прорисовка цветного квадрата в карте
*/
    void setRectangle(QColor color, int col, int row, double count);

    /**
* @brief Прорисовка картинки в карте
*/
    void setImage(int row, int colum, QString path, qreal rotation);

    /**
* @brief Установка ракеты в карту
*/
    void setPlayer(Player player);

    /**
* @brief Прорисовка команд и функции
*/
    void setSceneCommands();

    /**
* @brief Прорисовка команды
*/
    void setCommand(int num);

    /**
* @brief Прорисовка функции
*/
    void setFunc(int count, int countRect, int functionNumber);

    /**
* @brief Прорисовка цветного квадрата в командах
*/
    void setColor(int count);

    /**
* @brief Прорисовка карты
*/
    void drawMap(Map& map);

    /**
* @brief Удаление квадрата из карты
*/
    void deleteRect(int row, int colum);

    /**
* @brief Движение ракеты вперед
*/
    void moveForward(int rowNow, int columNow, int row, int colum);

    /**
* @brief Поворот ракеты направо
*/
    void moveTurnRight(int row, int colum);

    /**
* @brief Поворот ракеты налево
*/
    void moveTurnLeft(int row, int colum);

    /**
* @brief Перерисовка квадрата карты
*/
    void paintRect(int row, int colum, QColor);

    /**
* @brief Проверка цвета квадрата для выполнения команды
*/
    bool checkColor(ClickFunction*);

    /**
* @brief Масштабирование окна
*/
    virtual void resizeEvent(QResizeEvent* event) override;

private slots:

    /**
* @brief Отработка команд ракетой
*/
    void moveWithTime();

    /**
* @brief Открытие следующего уровня
*/
    void newLevel();

    /**
* @brief Обработчик нажатия на цвет
*/
    void color_Pressed(ClickColor*);

    /**
* @brief Обработчик нажатия на элемент функции
*/
    void function_Pressed(ClickFunction*);


    /**
* @brief Обработчик нажатия на команду
*/
    void command_Pressed(ClickCommand*);

    /**
* @brief Остановка движения ракеты
*/
    void on_Stop_clicked();

    /**
* @brief Начало движения ракеты
*/
    void on_Play_clicked();

    /**
* @brief Начать уровень заново
*/
    void on_Restart_clicked();

    /**
* @brief Выход в главное меню
*/
    void on_Back_clicked();

    /**
* @brief Как играть в игру
*/
    void on_question_clicked();

private:
    /**
* @brief Индекс функции для выполнения
*/
    int functionNow;

    /**
* @brief Индекс команды для выполнения
*/
    int commandNow;

    /**
* @brief Можно ли нажимать на функции и команды
*/
    bool clickable{ true };

    /**
* @brief Таймер
*/
    QTimer* timer;

    Ui::GameWindow *ui;
    QWidget* parentWindow;

    /**
* @brief Путь к карте
*/
    QString pathToMap;

    /**
* @brief Уровень
*/
    Map map;

    /**
* @brief Сцена карты
*/
    QGraphicsScene *scenemap;

    /**
* @brief Сцена функций
*/
    QGraphicsScene *scenecommands;

    /**
* @brief Квадрат с цветом
*/
    ClickColor* clickcolor;

    /**
* @brief Квадрат с командой
*/
    ClickCommand *clickcommand;

    /**
* @brief Квадрат со значенем цвета и команды
*/
    ClickFunction* clickfunction;

    /**
* @brief Нажатый квадрат функции
*/
    ClickFunction* clickFunctionNow;

    /**
* @brief Можно ли ракете двигаться дальше
*/
    bool move{ true };

    /**
* @brief Переменная для подсчета дополнительных линий в функциях, используется при прорисовке сцены функций
*/
    int count{ 0 };

    /**
* @brief Квадраты из функций
*/
    std::vector<std::vector<ClickFunction*>> vectorFunction;

    /**
* @brief Квадраты команд
*/
    std::vector<ClickCommand*> vectorCommand;

    /**
* @brief Квадраты цветов
*/
    std::vector<ClickColor*>vectorColor;

    /**
* @brief Квадраты названий функции, которые не нажимаются
*/
    std::vector<QGraphicsRectItem*> vectorNameFunction;

    /**
* @brief Количество звезд в карте
*/
    int countStars{ 0 };

    /**
* @brief Значение Ctrl+A
*/
    QShortcut* keyCtrlA;
    /**
* @brief Значение Ctrl+S
*/
    QShortcut* keyCtrlS;
    /**
* @brief Значение Ctrl+D
*/
    QShortcut* keyCtrlD;
protected:
    /**
* @brief Обработка нажатий на клавиши
*/
    void keyPressEvent(QKeyEvent* event);
};

#endif // GAMEWINDOW_H

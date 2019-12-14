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
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QString, QWidget* parent = nullptr);
    ~gamewindow() override;
    void setRectangle(QColor color, int col, int row, double count);
    void setImage(int row, int colum, QString path, qreal rotation);
    void setPlayer(Player player);
    void setSceneCommands();
    void setCommand(int num);

    void setFunc(int count, int countRect, int functionNumber);
    void setColor(int count);
    void drawMap(Map& map);
    void deleteRect(int row, int colum);
    void moveForward(int rowNow, int columNow, int row, int colum);
    void moveTurnRight(int row, int colum);
    void moveTurnLeft(int row, int colum);

    void paintRect(int row, int colum, QColor);
    bool checkColor(ClickFunction*);



    virtual void resizeEvent(QResizeEvent* event) override;

private slots:
    void moveWithTime();

    void newLevel();
    void color_Pressed(ClickColor*);
    void function_Pressed(ClickFunction*);
    void command_Pressed(ClickCommand*);

    void on_Stop_clicked();
    void on_Play_clicked();
    void on_Restart_clicked();
    void on_Back_clicked();

    void on_question_clicked();

private:
    int functionNow;
    int commandNow;
    bool clickable{ true };
    QTimer* timer;

    Ui::gamewindow *ui;
    QWidget* parentWindow;
    QString pathToMap;
    Map map;
    QMainWindow mainwindow;
    QGraphicsScene *scenemap;
    QGraphicsScene *scenecommands;
    QGraphicsRectItem *rect;
    ClickColor* clickcolor;
    ClickCommand *clickcommand;
    ClickFunction* clickfunction;
    ClickFunction* clickFunctionNow;
    QPainter *painter;
    bool move{ true };
    int count{ 0 };
    std::vector<int> vectorCommands;
    std::vector<std::vector<ClickFunction*>> vectorFunction;
    std::vector<ClickCommand*> vectorCommand;
    std::vector<ClickColor*>vectorColor;
    std::vector<QGraphicsRectItem*> vectorNameFunction;
    int countStars{ 0 };

    QShortcut* keyCtrlA;
    QShortcut* keyCtrlS;
    QShortcut* keyCtrlD;
protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // GAMEWINDOW_H

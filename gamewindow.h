#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QGraphicsView>
#include<QGraphicsScene>
#include <QGraphicsRectItem>
#include <QtGui>
#include <QtCore>

#include <QTransform>
#include <QGraphicsItem>
#include"map.h"
#include"clickcommand.h"
#include<vector>
#include"globals.h"
#include "dialog.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
    ~gamewindow() override;
    void setRectangle(QColor color, int col, int row, double count);
    void setImage(int row, int colum, QString path, qreal rotation);
    void setPlayer(Player player);
    void setSceneCommands();
    void setCommand(int num);

    void setFunc(int count, int countRect, int functionNumber);
	void setColor(int count);
    void drawMap(Map &map);
    void deleteRect(int row, int colum);
    void moveForward(int rowNow, int columNow, int row, int colum);
    void moveTurnRight(int row, int colum);
	void moveTurnLeft(int row, int colum);
	
	void paintRect(int row, int colum, QColor);
	void callFunction(int);
	bool checkColor(ClickFunction*);

virtual void resizeEvent(QResizeEvent *event) override;

private slots:

    void color_Pressed(ClickColor*);
	void function_Pressed();
	void command_Pressed(ClickCommand*);

    void on_Stop_clicked();
    void on_Play_clicked();
    void on_Restart_clicked();
    void on_Back_clicked();

private:
    Ui::gamewindow *ui;
	QWidget* parentWindow;
    Map map;
	QMainWindow mainwindow;
    QGraphicsScene *scenemap;
    QGraphicsScene *scenecommands;
    QGraphicsRectItem *rect;
	ClickColor* clickcolor;
    ClickCommand *clickcommand;
	ClickFunction* clickfunction;
    QPainter *painter;
    std::vector<int> vectorCommands;
	std::vector<std::vector<ClickFunction*>> vectorFunction;
	std::vector<ClickCommand*> vectorCommand;
	std::vector<ClickColor*>vectorColor;
	std::vector<QGraphicsRectItem*> vectorNameFunction;
	int countStars{ 0 };
};

#endif // GAMEWINDOW_H

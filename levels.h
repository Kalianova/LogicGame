#ifndef LEVELS_H
#define LEVELS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsRectItem>
#include <QDir>
#include <QMessageBox>
#include <QTextCodec>
#include "globals.h"
#include "vector"
#include <click.h>

namespace Ui {
class levels;
}

class levels : public QMainWindow
{
    Q_OBJECT

public:
    explicit levels(QWidget *parent = nullptr);
    std::vector<std::pair<QString, int>> pathsToLevel;
    std::vector<ClickColor*> rects;
    ~levels();

private slots:

    void color_Pressed(ClickColor*);

    void on_exit_clicked();

    void on_beginLevel_clicked();

    void on_create_clicked();

    void on_download_clicked();

    void on_deleteLevel_clicked();

private:
    Ui::levels *ui;
	QGraphicsScene* scene;
	QWidget* parentWindow;
    ClickColor* clickcolor{nullptr};
    void readLevels();
	void drawLevels();
    void openLevel(QString);
};

#endif // LEVELS_H

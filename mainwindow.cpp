#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "createmap.h"
#include "levels.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Главное меню");
    if (!QFile(QDir().currentPath() + "/map/config.txt").exists()) {
        QDir().mkdir("map");
        QFile read(":/map/config.txt");
        QFile write(QDir().currentPath() + "/map/config.txt");
        write.open(QFile::WriteOnly | QFile::Text | QFile::Append);
        read.open(QFile::ReadOnly | QFile::Text);
        QTextStream writeStreamConfig(&write);
        writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
        while (!read.atEnd()) {
            QString s = read.readLine();
            writeStreamConfig << s;
        }
        write.close();
        read.close();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_Exit_clicked() {
    this->close();
}


void MainWindow::on_NewGame_clicked() {
    QString name = globals::goToLevel();
    if (name == nullptr) {
        QMessageBox::information(this, "Уровни пройдены", "Выберите уровень в меню уровней");
    }
    else {
        GameWindow* window = new GameWindow(name, this);
        window->show();
        this->setVisible(false);
    }
}

void MainWindow::on_DevelopMap_clicked() {
    CreateMap *window = new CreateMap(this);
    window->show();
    this->hide();
}

void MainWindow::on_Levels_clicked() {
	Levels *window = new Levels(this);
	window->show();
	this->hide();
}

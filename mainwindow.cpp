#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "createmap.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
	this->setWindowTitle("Menu");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_Exit_clicked() {
    this->close();
}


void MainWindow::on_NewGame_clicked() {
  gamewindow *window = new gamewindow(this);
  window->show();
  this->setVisible(false);
}

void MainWindow::on_DevelopMap_clicked() {
    CreateMap *window = new CreateMap(this);
    window->show();
    this->hide();
}

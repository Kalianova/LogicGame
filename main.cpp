#include "mainwindow.h"
#include <QApplication>
#include <QFrame>
#include <QDir>
#include <QTextCodec>
#include <QMessageBox>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}

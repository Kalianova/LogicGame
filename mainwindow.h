#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
* @brief Класс для реализации главного меню игры
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /**
* @brief Начало игры
*/
    void on_NewGame_clicked();

    /**
* @brief Выход из игры
*/
    void on_Exit_clicked();

    /**
* @brief Создание уровня
*/
    void on_DevelopMap_clicked();

    /**
* @brief Меню уровней
*/
	void on_Levels_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

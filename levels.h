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
#include <QDir>
#include <QFileDialog>


namespace Ui {
class Levels;
}

/**
   * @brief Класс для реализации окна уровней и работы с ними
   */
class Levels : public QMainWindow
{
    Q_OBJECT

public:
    explicit Levels(QWidget *parent = nullptr);
    ~Levels();

private slots:

    /**
   * @brief Обработка нажатия на уровень
   */
    void level_Pressed(ClickColor*);

    /**
   * @brief Обработка нажатия на выход
   */
    void on_exit_clicked();

    /**
   * @brief Обработка нажатия на начать уровень
   */
    void on_beginLevel_clicked();

    /**
   * @brief Обработка нажатия на создать уровень
   */
    void on_create_clicked();

    /**
   * @brief Обработка нажатия на загрузить уровень
   */
    void on_download_clicked();

    /**
   * @brief Обработка нажатия на удалить уровень
   */
    void on_deleteLevel_clicked();

    /**
   * @brief Обработка нажатия на переместить уровень
   */
    void on_moveLevel_clicked();

private:
    Ui::Levels *ui;

    /**
* @brief Сцена уровней
*/
	QGraphicsScene* scene;

    /**
* @brief Главное меню
*/
	QWidget* parentWindow;

    /**
* @brief Нажатый уровень
*/
    ClickColor* clicklevel{nullptr};

    /**
* @brief Файловый менеджер
*/
    QFileDialog* dialog;

    /**
* @brief Пути к уровням и данные об их прохождении
*/
    std::vector<std::pair<QString, int>> pathsToLevel;

    /**
* @brief Все квадраты уровней
*/
    std::vector<ClickColor*> rects;

    /**
* @brief Зполнение массива уровней
*/
    void readLevels();

    /**
* @brief Прорисовка уровней
*/
	void drawLevels();

    /**
* @brief Открытие выбранного уровня
*/
    void openLevel(QString);

    /**
* @brief Перезапись файла со всеми уровнями значениями из массива уровней
*/
    void writeFile();

    /**
* @brief Происходит ли сейчас перемещение
*/
    bool moving{ false };
};

#endif // LEVELS_H

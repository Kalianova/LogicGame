#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <QMainWindow>
#include<QCheckBox>
#include <QGraphicsScene>
#include<click.h>
#include<vector>


namespace Ui {
class CreateMap;
}

    /**
* @brief Класс используемый для создания окна редактора карт
*/
class CreateMap : public QMainWindow
{
    Q_OBJECT

public:

    explicit CreateMap(QWidget* parent = nullptr);

    ~CreateMap();

private:
    Ui::CreateMap* ui;
 
    
    /**
* @brief Установка цветных квадратов в виде иконок CheckBox, которые обозначают цвета для покрски команд
*/
    void setCheckBoxColor(QColor, QCheckBox*);

    /**
* @brief Создание сцены(пустой карты)
*/
    void createScene();

    /**
 * @brief Создание квадрата с цветом в сцене
 */
    void createColor(QColor, double, int);

    /**
* @brief Создание квадрата с картинкой(ракета, звезда) в сцене
*/
    void createImage(QString, double, int, int);

    /**
* @brief Создание квадрата пустого квадрата в который можно будет вставить цвет и картинку
*/
    void createFunction(int, int, double);
    
    int sizeOfMap{ 10 };

    /**
* @brief Квадрат с цветом
*/
    ClickColor* clickcolor;

    /**
* @brief Квадрат с картинкой
*/
    ClickCommand* clickcommand;

    /**
* @brief Квадрат, в который можно вставить цвет и картинку
*/
    ClickFunction* clickfunction;

    /**
* @brief Квадрат который выделен сейчас
*/
    ClickFunction* clickFunctionNow{ nullptr };

    /**
* @brief Квадрат в котором находится ракета
*/
    ClickFunction* player{ nullptr };

    /**
* @brief Сцена создания карты
*/
    QGraphicsScene* createmap;

    /**
* @brief Главное меню
*/
    QWidget* parentWindow;

    /**
* @brief Проверка уникальности имени карты
*/
    bool isUnique(QString);

    /**
* @brief Все квадраты поля для заполнения карты
*/
    std::vector<ClickFunction*> vectorfunctions;

private slots:
    /**
* @brief Обработчик нажатия на цветной квадрат, который выбирается для создания карты
*/
    void color_Pressed(ClickColor*);

    /** 
* @brief Обработчик нажатия на квадрат с картинкой(ракета, звезда)
*/
    void image_Pressed(ClickCommand*);

    /**
* @brief Обработчик нажатия на закрашиваемые клетки карты
*/
    void rectangle_Pressed(ClickFunction*);

    /**
* @brief Обработка окна ввода размеры карты
*/
    void on_sizeOfMap_valueChanged(int arg1);

    /**
* @brief Обработка окна ввода размера 1 функции
*/
    void on_spinBoxFunction1_valueChanged(int arg1);

    /**
* @brief Обработка окна ввода размера 2 функции
*/
    void on_spinBoxFunction2_valueChanged(int arg1);

    /**
* @brief Обработка окна ввода размера 3 функции
*/
    void on_spinBoxFunction3_valueChanged(int arg1);

    /**
* @brief Обработка окна ввода размера 4 функции
*/
    void on_spinBoxFunction4_valueChanged(int arg1);

    /**
 * @brief Обработка окна ввода размера 5 функции
 */
    void on_spinBoxFunction5_valueChanged(int arg1);

    /**
 * @brief Обработка окна ввода наличия 1 функции в командах карты
 */
    void on_function1_stateChanged(int arg1);

    /**
 * @brief Обработка окна ввода наличия 2 функции в командах карты
 */
    void on_function2_stateChanged(int arg1);

    /**
 * @brief Обработка окна ввода наличия 3 функции в командах карты
 */
    void on_function3_stateChanged(int arg1);

    /**
 * @brief Обработка окна ввода наличия 4 функции в командах карты
 */
    void on_function4_stateChanged(int arg1);

    /**
* @brief Обработка окна ввода наличия 5 функции в командах карты
*/
    void on_function5_stateChanged(int arg1);

    /**
* @brief Отмена создания карты
*/
    void on_cancel_clicked();

    /**
* @brief Создание карты
*/
    void on_create_clicked();

    /**
* @brief Памятка по созданию карты
*/
    void on_howToCreate_clicked();
};

#endif // CREATEMAP_H

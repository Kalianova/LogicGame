#ifndef CLICK_H
#define CLICK_H

#include<QGraphicsSceneMouseEvent>
#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QGraphicsItem>


/**
* @brief Класс для управления цветным квадратом
*/
class ClickColor : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ClickColor(QColor, double, int);

    /**
* @brief Получение значения индекса
*/
    int getNumberColor() { return index; }

    /**
* @brief Установка значения индекса
*/
    void setIndex(int Index) { index = Index; }

    /**
* @brief Изменение нажатия на квадрат и оправка сигнала об этом
*/
    void changePress();

    /**
* @brief Проверка нажатия элемента
*/
    bool isPressed() { return pressed; }

    /**
* @brief Получение цвета элемента
*/
    QColor getColor() { return color; }

    /**
* @brief Установка размера квадрата
*/
    void setSize(double Size) { size = Size; }

    /**
* @brief Установка картинки
*/
    void setImage(QPixmap Image) { image = Image; }
    ~ClickColor() { delete pen; }
signals:
    /**
* @brief Сигнал нажатия на квадрат
*/
    void colorChanged(ClickColor*);
protected:

    /**
* @brief Нажатие на квадрат
*/
    void mousePressEvent(QGraphicsSceneMouseEvent*);
private:
    /**
* @brief Границы квадрата
*/
    QRectF boundingRect() const;

    /**
* @brief Прорисовка эемента цветом и если нужно добавление картинки
*/
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    /**
* @brief Для обводки элемента
*/
    QPen* pen;

    /**
* @brief Показывает выделен ли обводкой элемент
*/
    bool pressed{ false };

    QColor color;
    double size;
    int index;
    QPixmap image;
};

/**
* @brief Класс для управления квадратом с картинкой, без цветного фона
*/
class ClickCommand: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ClickCommand(QPixmap, double, int);

    /**
* @brief Изменение нажатия на квадрат
*/
    void changePress();

    /**
* @brief Проверка нажатия на элемент
*/
    bool isPressed() { return pressed; }

    /**
* @brief Получение картинки элемента
*/
    QPixmap getImage() { return image; }

    /**
* @brief Установка индекса элемента
*/
    void setIndex(int i) { index = i; }

    /**
* @brief Установка размера элемента
*/
    void setSize(double Size) { size = Size; }

    /**
* @brief Получение индекса элемента
*/
    int getNumberCommand() { return index; }
    ~ClickCommand() { delete pen; }
signals:

    /**
* @brief Сигнал нажатия на элемент
*/
    void commandChanged(ClickCommand*);
protected:

    /**
* @brief Нажатие на квадрат
*/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:

    /**
* @brief Границы квадрата
*/
    QRectF boundingRect() const;

    /**
* @brief Добавление в квадрат картинки
*/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
* @brief Для обводки элемента
*/
    QPen* pen;

    /**
* @brief Показывает выделен ли обводкой элемент
*/
    bool pressed{ false };
    QPixmap image;
    int index{ 0 };
    double size;
};


/**
* @brief Класс для управления цветным квадратом с картинкой
*/
class ClickFunction : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ClickFunction(double, int, int);
    /**
* @brief Изменение нажатия у элемента и квадратов цвета и команды, которые с ним связаны
*/
    void changePress();

    /**
* @brief Изменение нажатия у элемента
*/
    void changePressFunction();

    /**
* @brief Изменение нажатия у связанной команды
*/
    void changePressCommand();

    /**
* @brief Проверка нажатия элемента
*/
    bool isPressed() { return pressed; }

    /**
* @brief Получение цвета элемента
*/
    ClickColor* getColor() { return clickcolor; }

    /**
* @brief Получение команды элемента
*/
    ClickCommand* getCommand() { return clickcommand; }

    /**
* @brief Установка цвета
*/
    void setColor(ClickColor* ClickColor) { clickcolor = ClickColor; }

    /**
* @brief Установка команды
*/
    void setCommand(ClickCommand* ClickCommand) { clickcommand = ClickCommand; }

    /**
* @brief Установка размера
*/
    void setSize(double Size) { size = Size; }

    /**
* @brief Индекс обозначения клетки в карте
*/
    int getFunction();

    /**
* @brief Ряд элемента
*/
    int getRow() { return row; }

    /**
* @brief Колонка элемента
*/
    int getColum() { return colum; }
    ~ClickFunction();
signals:

    /**
* @brief Сигнал нажатия элемента, если он не был нажат
*/
    void functionChanged(ClickFunction*);

    /**
* @brief Сигнал нажатия элемента
*/
    void rectangleChanged(ClickFunction*);
protected:

    /**
* @brief Нажатие на элемент
*/
    void mousePressEvent(QGraphicsSceneMouseEvent*);

private:
    /**
* @brief Границы квадрата
*/
    QRectF boundingRect() const;

    /**
* @brief Добавление в квадрат картинки и цвета из связанных элементов: clickcolor, clickcommand
*/
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QColor color;
    double size;

    /**
* @brief Положение элемента в карте
*/
    int row, colum;

    /**
* @brief Выбран ли квадрат
*/
    bool pressed{ false };

    /**
* @brief Для обводки элемента
*/
    QPen* pen;
    QPixmap image;
    ClickColor* clickcolor{ nullptr };
    ClickCommand* clickcommand{ nullptr };
};

#endif // CLICK_H

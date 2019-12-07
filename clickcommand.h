#ifndef ClickCommand_H
#define ClickCommand_H

#include<QGraphicsSceneMouseEvent>
#include<QPainter>
#include<QStyleOptionGraphicsItem>
#include<QGraphicsItem>


class ClickColor : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	ClickColor(QColor, double, int);
	int getNumberColor() { return index; }
	void changePress();
	bool isPressed() { return pressed; }
	QColor getColor() { return color; }
	void setSize(double Size) { size = Size; }
	~ClickColor() {};
signals:
	void colorChanged(ClickColor*);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
private:
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	QColor color;
	double size;
	int index;
	bool pressed{ false };
	QPen* pen;
};

class ClickCommand: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ClickCommand(QPixmap, double, int);
	void changePress();
	bool isPressed() { return pressed; }
	QPixmap getImage() { return image; }
	void setIndex(int i) { index = i; }
	void setSize(double Size) { size = Size; }
	int getIndex() { return index; }
	int getNumberCommand() { return index; }
    ~ClickCommand(){}
signals:
	void commandChanged(ClickCommand*);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QPixmap image;
	QPen* pen;
	int index{ 0 };
	double size;
	int command{ 0 };
	bool pressed{ false };
};

class ClickFunction : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	ClickFunction(double);
	void changePress();
	bool isPressed() { return pressed; }
	ClickColor* getColor() { return clickcolor; }
	ClickCommand* getCommand() { return clickcommand; }
	void setColor(ClickColor* ClickColor) {
		clickcolor = ClickColor;
	}
	void setCommand(ClickCommand* ClickCommand) {
		clickcommand = ClickCommand;
	}
	void setSize(double Size) {
		size = Size;
	}
	int getFunction() {
		int color{ 0 }, command{ 0 };
		if (clickcolor != nullptr) {
			color = clickcolor->getNumberColor();
		}
		if (clickcommand != nullptr) {
			command = clickcommand->getNumberCommand();
		}
		return color + command;	}
	~ClickFunction() {};
signals:
	void functionChanged(ClickFunction*);
	void rectangleChanged(ClickFunction*);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*);
	
private:
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	QColor color;
	double size;
	int index;
	bool pressed{ false };
	QPen* pen;
	QPixmap image;
	ClickColor* clickcolor{ nullptr };
	ClickCommand* clickcommand{ nullptr };
};

#endif // ClickCommand_H

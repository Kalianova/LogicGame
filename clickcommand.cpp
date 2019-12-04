#include "clickcommand.h"


ClickColor::ClickColor(QColor Color, double Size, int Index)
	:color(Color), size(Size), index(Index)
{
	pen = new QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
}

void ClickColor::changePress()
{
	pressed = !pressed;
	update();
}

QRectF ClickColor::boundingRect() const
{
	return QRectF(-size / 2 , -size / 2 , size , size );
}

void ClickColor::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//painter->setPen(Qt::black);
	painter->setBrush(color);
	if (pressed) {
		painter->setPen(*pen);
	}
	painter->drawRect(-size / 2 + 2, -size / 2 + 2, size - 6, size - 6);
	
	Q_UNUSED(option)
	Q_UNUSED(widget)
}

void ClickColor::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	emit colorChanged(this);
	changePress();
	Q_UNUSED(event)
}

ClickCommand::ClickCommand(QPixmap Image, double Size, int Index)
    :image(Image), size(Size), index(Index)
{
	pen = new QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
}

void ClickCommand::changePress()
{
	pressed = !pressed;
	update();
}

QRectF ClickCommand::boundingRect() const
{
    return QRectF (-size/2 ,-size/2 ,size ,size);
}

void ClickCommand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    
	if (pressed) {
		painter->setPen(*pen);
	}
	painter->drawRect(-size / 2 + 3, -size / 2 + 3, size - 6, size - 6);
	painter->drawPixmap(QRect(-size / 2 + 3, -size / 2 + 3, size - 6, size - 6), image);
	
	Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ClickCommand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	emit commandChanged(this);
	changePress();
	Q_UNUSED(event)
}


ClickFunction::ClickFunction(double Size)
	:size(Size)
{
	pen = new QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
}

void ClickFunction::changePress()
{
	pressed = !pressed;
	if (clickcolor != nullptr) {
		clickcolor->changePress();
	}
	if (clickcommand != nullptr) {
		clickcommand->changePress();
	}
	update();
}

QRectF ClickFunction::boundingRect() const
{
	return QRectF(-size / 2 , -size / 2 , size , size );
}

void ClickFunction::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (clickcolor != nullptr) {
		painter->setBrush(clickcolor->getColor());
	}
	
	if (pressed) {
		painter->setPen(*pen);
	}
	painter->drawRect(-size / 2 + 3, -size / 2 + 3, size - 6, size - 6);
	if (clickcommand != nullptr) {
		painter->drawPixmap(QRect(-size / 2 + 3, -size / 2 + 3, size - 6, size - 6), clickcommand->getImage());
	}
	Q_UNUSED(option)
	Q_UNUSED(widget)
}


void ClickFunction::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (!pressed) {
		emit functionChanged();
		changePress();
	}
	emit rectangleChanged(this);
	Q_UNUSED(event)
}

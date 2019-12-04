#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>
#include <QGraphicsView>


gamewindow::gamewindow(QWidget* parent) :
	QMainWindow(parent),
	parentWindow(parent),
	ui(new Ui::gamewindow)
{
	ui->setupUi(this);
	this->setWindowTitle("Game");
	this->resize(804, 500);
	
	scenemap = new QGraphicsScene();
	scenecommands = new QGraphicsScene();

	ui->frame->resize(458, 458);
	ui->frame_2->resize(317, 458);
	ui->graphicsView->resize(430, 430);
	ui->commands->resize(289, 430);

	scenemap->setBackgroundBrush(QBrush(Qt::black));
	map.ReadFrom(":/map/map1.txt");

	ui->graphicsView->setScene(scenemap);
	ui->commands->setScene(scenecommands);

	scenemap->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);
	scenecommands->setSceneRect(0, 0, ui->commands->width() - 4, ui->commands->height()- 4);
	//this->resizeEvent(new QResizeEvent(QSize(1000, 1000), QSize(1000, 1000)));
}

gamewindow::~gamewindow() {
    delete ui;
}

void gamewindow::setRectangle(QColor color, int row, int col, double count) {
	rect = new QGraphicsRectItem();
	double size = (this->ui->graphicsView->height() - 4) / count;
	rect->setRect(size * col, size * row,
		size - 4, size - 4);
	rect->setBrush(color);
	if (color != Qt::black) {
		scenemap->addItem(rect);
	}
}

void gamewindow::setImage(int row, int colum, QString path, qreal rotation)
{
	QPixmap image;
	double size = (this->ui->graphicsView->height() - 4) / map.getSize();
	image.load(path);
	image = image.scaled(size, size);
	QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(image);
	pix->setRotation(rotation);
	pix->setParentItem(scenemap->itemAt(row * size + size/2 , colum * size + size/2 , QTransform()));
	switch ((int)rotation) {
	case 0:
		pix->setPos(row * size, colum * size);
		break;
	case 90:
		pix->setPos(row * size + size, colum * size);
		break;
	case 180:
		pix->setPos(row * size + size, colum * size + size);
		break;
	case 270:
		pix->setPos(row * size, colum * size + size);
		break;
	}
}

void gamewindow::setPlayer(Player player) {
	setImage(map.player.getColum(), map.player.getRow(), ":/image/rocket.png", map.player.getRotation());
}

void gamewindow::setSceneCommands() {
	vectorFunction.resize(map.getFunctionsCount());
	vectorNameFunction.resize(0);
	int count = 0;
	for (int i = 0; i < map.getFunctionsCount(); i++) {
		setFunc(i + count, map.getFunction(i), i);
		count += map.getFunction(i) / 5;
	}
	if (vectorCommand.size() != map.getCommandsCount()) {
		vectorFunction[0][0]->changePress();
	}
	for (int i = 0; i < map.getCommandsCount(); i++) {
		setCommand(i);
	}
	for (int i = 0; i < map.getColorsCount(); i++) {
		setColor(i);
	}
}

void gamewindow::setCommand(int num) {
	double size = (this->ui->commands->width() - 4) / (SIZE_OF_FUNCTIONS + 3);
	if (vectorCommand.size() > num) {
		vectorCommand[num]->setPos(size / 2, size / 2 + size * num);
		vectorCommand[num]->setSize(size);
		vectorCommand[num]->update();
	}
	else {
		QPixmap image;
		switch (map.getCommand(num)) {
		case 1:
			image.load(":/image/arrow_up");
			clickcommand = new ClickCommand(image, size, 1);
			break;
		case 2:
			image.load(":/image/arrow_right");
			clickcommand = new ClickCommand(image, size, 2);
			break;
		case 3:
			image.load(":/image/arrow_left");
			clickcommand = new ClickCommand(image, size, 3);
			break;
		case 4:
			image.load(":/image/blue_brush");
			clickcommand = new ClickCommand(image, size, 4);
			break;
		case 5:
			image.load(":/image/dark_magenta_brush");
			clickcommand = new ClickCommand(image, size, 5);
			break;
		case 6:
			image.load(":/image/red_brush");
			clickcommand = new ClickCommand(image, size, 6);
			break;
		case 7:
			image.load(":/image/dark_yellow_brush");
			clickcommand = new ClickCommand(image, size, 7);
			break;
		case 8:
			image.load(":/image/function1");
			clickcommand = new ClickCommand(image, size, 8);
			break;
		case 9:
			image.load(":/image/function2");
			clickcommand = new ClickCommand(image, size, 9);
			break;
		}
		clickcommand->setPos(size / 2, size / 2 + size * num);
		connect(clickcommand, SIGNAL(commandChanged(ClickCommand*)), this, SLOT(command_Pressed(ClickCommand*)));
		scenecommands->addItem(clickcommand);
		vectorCommand.push_back(clickcommand);
	}
}

void gamewindow::setFunc(int count, int countRect, int functionNumber) {
	double size = (this->ui->commands->width() - 4) / (SIZE_OF_FUNCTIONS + 3);
	QPixmap image;
	image.load(":/image/function" + QString::number(functionNumber + 1));
	image = image.scaled(size - 4, size - 4);

	QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(image);
	rect = new QGraphicsRectItem();
	rect->setRect(size + 2,
		size * count + 2,
		size - 4,
		size - 4);
	rect->setBrush(Qt::gray);

	pix->setPos(size + 2, size * count + 2);
	pix->setParentItem(rect);

	scenecommands->addItem(rect);
	vectorNameFunction.push_back(rect);

	for (size_t i = 0; i < countRect; i++) {
		if (vectorFunction[functionNumber].size() > i) {
			vectorFunction[functionNumber][i]->setPos(size * 2.5 + size * (i % 5),
				size * (count + (i) / 5 + 0.5));
			vectorFunction[functionNumber][i]->setSize(size);
			vectorFunction[functionNumber][i]->update();
		}
		else {
			clickfunction = new ClickFunction(size);
			clickfunction->setPos(size * 2.5 + size * (i % 5),
				size * (count + (i) / 5 + 0.5));
			connect(clickfunction, SIGNAL(functionChanged()), this, SLOT(function_Pressed()));
			vectorFunction[functionNumber].push_back(clickfunction);
			scenecommands->addItem(clickfunction);
		}
	}
}

void gamewindow::setColor(int num) {
	double size = (this->ui->commands->width() - 4) / (SIZE_OF_FUNCTIONS + 3);
	if (vectorColor.size() > num) {
		vectorColor[num]->setSize(size);
		vectorColor[num]->setPos(size * (SIZE_OF_FUNCTIONS + 3) - size / 2,
			size / 2 + size * num);
		vectorColor[num]->update();
	}
	else {
		clickcolor = new ClickColor(map.getColor(num), size, 1);
		clickcolor->setPos(size * (SIZE_OF_FUNCTIONS + 3) - size / 2,
			size / 2 + size * num);
		connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
		scenecommands->addItem(clickcolor);
		vectorColor.push_back(clickcolor);
	}
}

void gamewindow::drawMap(Map& map) {
	scenemap->width();
	for (int i = 0; i < map.getSize(); ++i) {
		for (int j = 0; j < map.getSize(); ++j) {
			this->setRectangle(map.ColorOfRect(i, j), i, j, map.getSize());
			if (map.getNumber(i, j) >= 5) {
				setImage(j, i, ":/image/star.png", 0);
				countStars++;
			}
		}
	}
}

void gamewindow::deleteRect(int row, int colum) {
	double size = (this->ui->graphicsView->height() - 4) / map.getSize();
	if (scenemap->itemAt(row * size + size / 2, colum * size + size / 2, QTransform()) != nullptr) {
		delete scenemap->itemAt(row * size + size / 2, colum * size + size / 2, QTransform());
	}
}

void gamewindow::moveForward(int rowNow, int columNow, int row, int colum)
{
	double size = (this->ui->graphicsView->height() - 4)/10;
	if (row >= 0 && colum >= 0 && row < map.getSize() && colum < map.getSize()) {
		if (map.ColorOfRect(row, colum) != Qt::black) {
			deleteRect(rowNow, columNow);
			setRectangle(map.ColorOfRect(rowNow, columNow), rowNow, columNow, map.getSize());
			deleteRect(row, colum);
			setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
			map.player.setPosition(row, colum);
			setPlayer(map.player);
			if (map.getNumber(row, colum) >= 5) {
				countStars--;
			}
			if (countStars == 0) {
				Dialog* window = new Dialog();
				window->setWindow("Congratulations. Level passed.", "Next Level");
				window->show();
				connect(window, SIGNAL(button_pushed()), this, SLOT(on_Stop_clicked()));
			}
			return;
		}
	}

}

void gamewindow::moveTurnRight(int row, int colum)
{
	deleteRect(row, colum);
	setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
	map.player.moveRight();
	setPlayer(map.player);
}

void gamewindow::moveTurnLeft(int row, int colum)
{
	deleteRect(row, colum);
	setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
	map.player.moveLeft();
	setPlayer(map.player);
}



void gamewindow::paintRect(int row, int colum, QColor color)
{
	deleteRect(row, colum);
	setRectangle(color, row, colum, map.getSize());
	setPlayer(map.player);
}

void gamewindow::callFunction(int num)
{
	for (ClickFunction* function : vectorFunction[num]) {
		if (checkColor(function)) {
			switch (function->getCommand()->getIndex()) {
			case 0:
				break;
			case 1:
				switch (map.player.getRotation()) {
				case 0:
					moveForward(map.player.getRow(), map.player.getColum(), map.player.getRow() - 1, map.player.getColum());
					break;
				case 90:
					moveForward(map.player.getRow(), map.player.getColum(), map.player.getRow(), map.player.getColum() + 1);
					break;
				case 180:
					moveForward(map.player.getRow(), map.player.getColum(), map.player.getRow() + 1, map.player.getColum());
					break;
				case 270:
					moveForward(map.player.getRow(), map.player.getColum(), map.player.getRow(), map.player.getColum() - 1);
					break;
				}
				break;
			case 2:
				moveTurnRight(map.player.getRow(), map.player.getColum());
				break;
			case 3:
				moveTurnLeft(map.player.getRow(), map.player.getColum());
				break;
			case 4:
				map.setColor(map.player.getRow(), map.player.getColum(), "1");
				paintRect(map.player.getRow(), map.player.getColum(), Qt::blue);
				break;
			case 5:
				map.setColor(map.player.getRow(), map.player.getColum(), "2");
				paintRect(map.player.getRow(), map.player.getColum(), Qt::darkMagenta);
				break;
			case 6:
				map.setColor(map.player.getRow(), map.player.getColum(), "3");
				paintRect(map.player.getRow(), map.player.getColum(), Qt::red);
				break;
			case 7:
				map.setColor(map.player.getRow(), map.player.getColum(), "4");
				paintRect(map.player.getRow(), map.player.getColum(), Qt::darkYellow);
				break;
			default:
				callFunction(function->getCommand()->getIndex() % 8);
				break;
			}
		}

	}
	if (countStars != 0) {
		Dialog* window = new Dialog();
		window->show();
		connect(window, SIGNAL(button_pushed()), this, SLOT(on_Stop_clicked()));
	}
}

bool gamewindow::checkColor(ClickFunction* function)
{
	if (function->getColor() == nullptr && function->getCommand() != nullptr) {
		return true;
	}
	else {
		return function->getCommand() != nullptr && 
			function->getColor()->getColor() == map.ColorOfRect(map.player.getRow(), map.player.getColum());
	}
}

void gamewindow::resizeEvent(QResizeEvent* event) {
	scenemap->clear();
	if (ui->centralwidget->width() - ui->frame->height() + ui->frame->geometry().x() >= 300) {
		ui->frame->setGeometry(ui->frame->geometry().x(), ui->frame->geometry().y(), ui->frame->height(), ui->frame->height());
	}
	else {
		ui->frame->setGeometry(ui->frame->geometry().x(), ui->frame->geometry().y(), ui->centralwidget->width() - 300, ui->centralwidget->width() - 300);
	}
	ui->frame_2->setGeometry(ui->frame->geometry().x() + ui->frame->height(), ui->frame->geometry().y(), ui->centralwidget->width() - ui->frame->geometry().x() * 2 - ui->frame->height(), ui->frame->height());
	scenemap->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);
	scenecommands->setSceneRect(0, 0, ui->commands->width() - 4, ui->commands->height() - 4);

	ui->graphicsView->setScene(scenemap);
	ui->commands->setScene(scenecommands);
	drawMap(map);
	setPlayer(map.player);
	for (QGraphicsRectItem* i : vectorNameFunction) {
		delete i;
	}
	setSceneCommands();
}

void gamewindow::color_Pressed(ClickColor* color) {
	for (int i = 0; i < vectorFunction.size(); i++) {
		for (ClickFunction* function : vectorFunction[i]) {
			if (function->isPressed()) {
				if (function->getColor() != nullptr && function->getColor() != color) {
					function->getColor()->changePress();
				}
				if (color->isPressed()) {
					function->setColor(nullptr);
				}
				else {
					function->setColor(color);
				}
				function->update();
				break;
			}
		}
	}
}

void gamewindow::function_Pressed() {
	for (int i = 0; i < vectorFunction.size(); i++) {
		for (ClickFunction* function : vectorFunction[i]) {
			if (function->isPressed()) {
				function->changePress();
				if (function->getCommand() == nullptr) {
					function->setColor(nullptr);
				}
				break;
			}
		}
	}
}

void gamewindow::command_Pressed(ClickCommand* command) {
	for (int i = 0; i < vectorFunction.size(); i++) {
		for (ClickFunction* function : vectorFunction[i]) {
			if (function->isPressed()) {
				if (function->getCommand() != nullptr && function->getCommand()!=command) {
					function->getCommand()->changePress();
				}
				if (command->isPressed()) {
					function->setCommand(nullptr);
				}
				else {
					function->setCommand(command);
				}
				function->update();
				break;
			}
		}
	}
}

void gamewindow::on_Stop_clicked() {
	scenemap->clear();
	drawMap(map);
	countStars = 0;
	map.ReadFrom(":/map/map1.txt");
	drawMap(map);
	map.player = Player(map.player.getBeginRow(), map.player.getBeginColum(), map.player.getBeginRotation());
	setPlayer(map.player);
}

void gamewindow::on_Play_clicked() {
	callFunction(0);
}

void gamewindow::on_Restart_clicked() {
	scenecommands->clear();
	vectorFunction.resize(0);
	vectorColor.resize(0);
	vectorCommand.resize(0);

	setSceneCommands();
	on_Stop_clicked();
}

void gamewindow::on_Back_clicked() {
	parentWindow->setVisible(true);
	this->close();
}
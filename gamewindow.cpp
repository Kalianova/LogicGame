#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>
#include <QKeyEvent>
#include<QMessageBox>


GameWindow::GameWindow(QString path, QWidget* parent) :
    QMainWindow(parent),
    parentWindow(parent),
    ui(new Ui::GameWindow),
    pathToMap(path)
{
    ui->setupUi(this);
    this->setWindowTitle("Игра");
    this->resize(1000, 585);
    
    scenemap = new QGraphicsScene();
    scenecommands = new QGraphicsScene();

    ui->frame->resize(486, 486);
    ui->frame_2->resize(485, 486);
    ui->graphicsView->resize(452, 452);
    ui->commands->resize(452, 452);

    scenemap->setBackgroundBrush(QBrush(Qt::black));
    map.ReadFrom(pathToMap);
    ui->LevelName->setText(globals::nameOfLevelFromPath(pathToMap));
    ui->graphicsView->setScene(scenemap);
    ui->commands->setScene(scenecommands);

    timer = new QTimer(this);
    timer->setInterval(170);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveWithTime()));

    keyCtrlA = new QShortcut(this); 
    keyCtrlA->setKey(Qt::CTRL + Qt::Key_A); 
    connect(keyCtrlA, SIGNAL(activated()), this, SLOT(on_Play_clicked()));

    keyCtrlS = new QShortcut(this); 
    keyCtrlS->setKey(Qt::CTRL + Qt::Key_S); 
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(on_Stop_clicked()));

    keyCtrlD = new QShortcut(this); 
    keyCtrlD->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrlD, SIGNAL(activated()), this, SLOT(on_Restart_clicked()));

}

GameWindow::~GameWindow() {
    delete ui;
    delete timer;
    delete scenemap;
    delete scenecommands;
    delete keyCtrlA;
    delete keyCtrlS;
    delete keyCtrlD;
}

void GameWindow::setRectangle(QColor color, int row, int col, double count) {
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    double size = (this->ui->graphicsView->height() - 4) / count;
    rect->setRect(size * col, size * row,
        size - 4, size - 4);
    rect->setBrush(color);
    if (color != Qt::black) {
        scenemap->addItem(rect);
    }
}

void GameWindow::setImage(int row, int colum, QString path, qreal rotation) {
    QPixmap image;
    double size = (this->ui->graphicsView->height() - 4) / map.getSize();
    image.load(path);
    image = image.scaled(size, size);
    QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(image);
    pix->setRotation(rotation);
    pix->setParentItem(scenemap->itemAt(row * size + size/2 , colum * size + size/2 , QTransform()));
    switch ((int)rotation) {
    case 0:
        pix->setPos(row * size , colum * size);
        break;
    case 90:
        pix->setPos(row * size + size, colum * size);
        break;
    case 180:
        pix->setPos(row * size + size, colum * size + size) ;
        break;
    case 270:
        pix->setPos(row * size,colum * size + size);
        break;
    }
}

void GameWindow::setPlayer(Player player) {
    setImage(map.player.getColum(), map.player.getRow(), ":/image/rocket.png", map.player.getRotation());
}

void GameWindow::setSceneCommands() {
    double size = (ui->commands->width() - 4) / SIZE_OF_FUNCTIONS;
    double sizeCommand = (ui->commands->width() - 4) / SIZE_OF_COMMANDS;
    move = true;
    vectorFunction.resize(map.getFunctionsCount());
    vectorNameFunction.resize(0);
    int count = 0;
    for (int i = 0; i < map.getFunctionsCount(); i++) {
        setFunc(i + count, map.getFunction(i), i);
        count += map.getFunction(i)/10 / (SIZE_OF_FUNCTIONS + 1);
    }
    if (vectorCommand.size() != map.getCommandsCount()) {
        vectorFunction[0][0]->changePress();
        clickFunctionNow = vectorFunction[0][0];
    }
    for (int i = 0; i < map.getCommandsCount(); i++) {
        setCommand(i);
    }
    for (int i = 0; i < map.getColorsCount(); i++) {
        setColor(i);
    }

    if (vectorColor.size() > map.getColorsCount()) {
        vectorColor[map.getColorsCount()]->setSize(sizeCommand);
        vectorColor[map.getColorsCount()]->setPos(sizeCommand / 2 + sizeCommand * map.getColorsCount(),
            sizeCommand * 1.5);
        vectorColor[map.getColorsCount()]->update();
    }
    else {
        clickcolor = new ClickColor(Qt::white, sizeCommand, 1);
        clickcolor->setPos(sizeCommand / 2 + sizeCommand * map.getColorsCount(),
            sizeCommand *1.5);
        QPixmap image;
        image.load(":/image/eraser.png");
        clickcolor->setImage(image);
        connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
        scenecommands->addItem(clickcolor);
        vectorColor.push_back(clickcolor);
    }
    if (ui->commands->height() - 4 > size* (count + map.getFunctionsCount()) + sizeCommand * 2.4 ) {
        scenecommands->setSceneRect(0, 0, ui->commands->width() - 4, ui->commands->height() - 4);
    }
    else {
        scenecommands->setSceneRect(0, 0, ui->commands->width() - 4, size * (count + map.getFunctionsCount()) + sizeCommand * 2.4 );
    }
}

void GameWindow::setCommand(int num) {
    double size = (this->ui->commands->width() - 4) / SIZE_OF_COMMANDS;
    if (vectorCommand.size() > num) {
        vectorCommand[num]->setPos(size * num + size / 2,
            size / 2);
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
        case 10:
            image.load(":/image/function3");
            clickcommand = new ClickCommand(image, size, 8);
            break;
        case 11:
            image.load(":/image/function4");
            clickcommand = new ClickCommand(image, size, 9);
            break;
        case 12:
            image.load(":/image/function5");
            clickcommand = new ClickCommand(image, size, 8);
            break;
        }
        clickcommand->setPos(size * num + size / 2, size / 2);
        connect(clickcommand, SIGNAL(commandChanged(ClickCommand*)), this, SLOT(command_Pressed(ClickCommand*)));
        scenecommands->addItem(clickcommand);
        vectorCommand.push_back(clickcommand);
    }
}

void GameWindow::setFunc(int count, int countRect, int functionNumber) {
    double size = (this->ui->commands->width() - 4) / (SIZE_OF_FUNCTIONS + 1);
    double sizeCommands = (this->ui->commands->width() - 4) / SIZE_OF_COMMANDS;
    QPixmap image;
    image.load(":/image/function" + QString::number(countRect%10));
    image = image.scaled(size - 4, size - 4);

    QGraphicsPixmapItem* pix = new QGraphicsPixmapItem(image);
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(2,
        sizeCommands*2.4 +size * count + 2 + functionNumber * 0.2 * size,
        size - 4,
        size - 4);
    rect->setBrush(Qt::gray);

    pix->setPos(2, sizeCommands * 2.4 + size* count + 2 + functionNumber*0.2*size);
    pix->setParentItem(rect);

    scenecommands->addItem(rect);
    vectorNameFunction.push_back(rect);

    for (size_t i = 0; i < countRect/10; i++) {
        if (vectorFunction[functionNumber].size() > i) {
            vectorFunction[functionNumber][i]->setPos(size + size * (i % SIZE_OF_FUNCTIONS) + size/2,
                size * (count + (i) / SIZE_OF_FUNCTIONS + 0.5) + sizeCommands * 2.4 + functionNumber*size*0.2);
            vectorFunction[functionNumber][i]->setSize(size);
            vectorFunction[functionNumber][i]->update();
        }
        else {
            clickfunction = new ClickFunction(size, functionNumber, i);
            clickfunction->setPos(size+ size * (i % SIZE_OF_FUNCTIONS) + size/2,
                size * (count + (i) / SIZE_OF_FUNCTIONS + 0.5 ) + sizeCommands * 2.4+ functionNumber * size*0.2);
            connect(clickfunction, SIGNAL(functionChanged(ClickFunction*)), this, SLOT(function_Pressed(ClickFunction*)));
            vectorFunction[functionNumber].push_back(clickfunction);
            scenecommands->addItem(clickfunction);
        }
    }
}

void GameWindow::setColor(int num) {
    double size = (this->ui->commands->width() - 4) / SIZE_OF_COMMANDS;
    if (vectorColor.size() > num) {
        vectorColor[num]->setSize(size);
        vectorColor[num]->setPos(size * num + size / 2,
            size + size / 2);
        vectorColor[num]->update();
    }
    else {
        clickcolor = new ClickColor(map.getColor(num), size, 1);
        clickcolor->setPos(size * num + size / 2,
           size + size / 2);
        connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
        scenecommands->addItem(clickcolor);
        vectorColor.push_back(clickcolor);
    }
}

void GameWindow::drawMap(Map& map) {
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

void GameWindow::deleteRect(int row, int colum) {
    double size = (this->ui->graphicsView->height() - 4) / map.getSize();
    if (scenemap->itemAt(colum * size + size / 2, row * size + size / 2, QTransform()) != nullptr) {
        delete scenemap->itemAt(colum * size + size / 2, row * size + size / 2, QTransform());
    }
}

void GameWindow::moveForward(int rowNow, int columNow, int row, int colum) {
    double size = (this->ui->graphicsView->height() - 4) / map.getSize();
    if (row >= 0 && colum >= 0 && row < map.getSize() && colum < map.getSize()) {
        if (map.ColorOfRect(row, colum) != Qt::black){
            deleteRect(rowNow, columNow);
            setRectangle(map.ColorOfRect(rowNow, columNow), rowNow, columNow, map.getSize());
            deleteRect(row, colum);
            setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
            map.player.setPosition(row, colum);
            setPlayer(map.player);
            if (map.getNumber(row, colum) >= 5) {
                countStars--;
                map.setColor(row, colum, std::to_string(map.getNumber(row, colum) - 5));
            }
            return;
        }
        else {
            move = false;
        }
    }
    else {
        move = false;
    }
}

void GameWindow::moveTurnRight(int row, int colum) {
    deleteRect(row, colum);
    setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
    map.player.moveRight();
    setPlayer(map.player);
}

void GameWindow::moveTurnLeft(int row, int colum) {
    deleteRect(row, colum);
    setRectangle(map.ColorOfRect(row, colum), row, colum, map.getSize());
    map.player.moveLeft();
    setPlayer(map.player);
}

void GameWindow::paintRect(int row, int colum, QColor color) {
    deleteRect(row, colum);
    setRectangle(color, row, colum, map.getSize());
    setPlayer(map.player);
}

void GameWindow::moveWithTime() {
    if (move == false) {
        int k = QMessageBox::information(this, "Уровень не решен", "Попробуйте еще раз", "OK");
        on_Stop_clicked();
        timer->stop();
        clickable = true;
        move = true;
    }
    else {
        if (countStars == 0) {
            int k = QMessageBox::question(this, "Уровень решен", "Поздравляю",  "Остаться на этом", "Следующий уровень", 0,1);
            if (k) {
                globals::setLevelDone(pathToMap);
                pathToMap = globals::goToLevel();
                newLevel();
            }
            timer->stop();
            move = true;
        }
        else {
            if (commandNow == vectorFunction[functionNow].size()) {
                move = false;
            }
            else {
                clickFunctionNow->changePressFunction();               
                ClickFunction* function = vectorFunction[functionNow][commandNow];
                function->changePressFunction();
                clickFunctionNow = function;
                if (checkColor(function)) {
                    switch (function->getCommand()->getNumberCommand()) {
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
                        functionNow = function->getCommand()->getNumberCommand() % 8;
                        commandNow = -1;
                        break;
                    }
                }
                commandNow++;
            }
        }
    }
}

bool GameWindow::checkColor(ClickFunction* function) {
    if (function->getColor() == nullptr && function->getCommand() != nullptr) {
        return true;
    }
    else {
        return function->getCommand() != nullptr &&
            function->getColor()->getColor() == map.ColorOfRect(map.player.getRow(), map.player.getColum());
    }
}

void GameWindow::resizeEvent(QResizeEvent* event) {
    scenemap->clear();
    if (ui->centralwidget->width() - ui->frame->height() + ui->frame->geometry().x() >= 300) {
        ui->frame->setGeometry(ui->frame->geometry().x(), ui->frame->geometry().y(), ui->frame->height(), ui->frame->height());
    }
    else {
        ui->frame->setGeometry(ui->frame->geometry().x(), ui->frame->geometry().y(), ui->centralwidget->width() - 300, ui->centralwidget->width() - 300);
    }
    ui->frame_2->setGeometry(ui->frame->geometry().x() + ui->frame->height(), ui->frame->geometry().y(), ui->centralwidget->width() - ui->frame->geometry().x() * 2 - ui->frame->height(), ui->frame->height());
    scenemap->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);

    ui->graphicsView->setScene(scenemap);
    ui->commands->setScene(scenecommands);
    countStars = 0;
    drawMap(map);
    setPlayer(map.player);

    for (QGraphicsRectItem* i : vectorNameFunction) {
        delete i;
    }
    setSceneCommands();
}

void GameWindow::color_Pressed(ClickColor* color) {
    if (clickable) {
        if (clickFunctionNow->getColor() != nullptr && clickFunctionNow->getColor() != color) {
            clickFunctionNow->getColor()->changePress();
        }
        if (color->isPressed()) {
            clickFunctionNow->setColor(nullptr);
        }
        else {
            if (color->getColor() == Qt::white) {
                clickFunctionNow->changePress();
                if (clickFunctionNow->getColor() != nullptr) {
                    clickFunctionNow->getColor()->changePress();
                }
                clickFunctionNow->setCommand(nullptr);
                clickFunctionNow->setColor(nullptr);
                clickFunctionNow->changePress();
                color->changePress();
            }
            else {
                clickFunctionNow->setColor(color);
            }
        }
        clickFunctionNow->update();
    }
    else {
        color->changePress();
    }
}

void GameWindow::function_Pressed(ClickFunction* pressedFunction) {
    if (clickable) {
        clickFunctionNow->changePress();
        if (clickFunctionNow->getCommand() == nullptr) {
            clickFunctionNow->setColor(nullptr);
        }
        clickFunctionNow = pressedFunction;
    }
    else {
        pressedFunction->changePress();
    }
}

void GameWindow::command_Pressed(ClickCommand* command) {
    if (clickable) {
        if (clickFunctionNow->getCommand() != nullptr && clickFunctionNow->getCommand() != command) {
            clickFunctionNow->getCommand()->changePress();
        }
        if (command->isPressed()) {
            clickFunctionNow->setCommand(nullptr);
        }
        else {
            clickFunctionNow->setCommand(command);
        }
        clickFunctionNow->update();
    }
    else {
        command->changePress();
    }
}

void GameWindow::on_Stop_clicked() {
    clickFunctionNow->changePressCommand();
    clickable = true;
    timer->stop();
    scenemap->clear();
    countStars = 0;
    map.ReadFrom(pathToMap);
    drawMap(map);
    map.player = Player(map.player.getBeginRow(), map.player.getBeginColum(), map.player.getBeginRotation());
    setPlayer(map.player);
}

void GameWindow::on_Play_clicked() {
    if (clickable) {
        clickFunctionNow->changePressCommand();
        clickable = false;
        functionNow = 0;
        commandNow = 0;
        timer->start();
    }
}

void GameWindow::newLevel() {
    if (pathToMap == nullptr) {
        QMessageBox::information(this, "Уровни пройдены", "Выберите уровень в меню уровней");
    }
    else {
        map.ReadFrom(pathToMap);
        ui->LevelName->setText(globals::nameOfLevelFromPath(pathToMap));
        on_Restart_clicked();
    }
    on_Stop_clicked();
}

void GameWindow::on_Restart_clicked() {
    clickable = true;
    if (globals::goToLevel() != nullptr) {
        scenecommands->clear();
        vectorFunction.resize(0);
        vectorColor.resize(0);
        vectorCommand.resize(0);
        setSceneCommands();
        on_Stop_clicked();
    }
}

void GameWindow::on_Back_clicked() {
    parentWindow->setVisible(true);
    this->close();
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    if (clickable) {
        QCoreApplication::processEvents();
        int key = event->key();
        int colum = clickFunctionNow->getColum();
        int row = clickFunctionNow->getRow();
        if (key == Qt::Key_W || key == 1062 || key == Qt::Key_Up) {
            if (row == 0) {
                if (0 <= colum - SIZE_OF_FUNCTIONS) {
                    function_Pressed(vectorFunction[row][colum - SIZE_OF_FUNCTIONS]);
                }
                else {
                    function_Pressed(vectorFunction[vectorFunction.size() - 1][colum % SIZE_OF_FUNCTIONS + SIZE_OF_FUNCTIONS * ((vectorFunction[vectorFunction.size() - 1].size() - colum % SIZE_OF_FUNCTIONS - 1)
                        / SIZE_OF_FUNCTIONS)]);
                }
            }
            else {
                if (0 <= colum - SIZE_OF_FUNCTIONS) {
                    function_Pressed(vectorFunction[row][colum - SIZE_OF_FUNCTIONS]);
                }
                else {
                    function_Pressed(vectorFunction[row - 1]
                        [colum % SIZE_OF_FUNCTIONS + SIZE_OF_FUNCTIONS * ((vectorFunction[row - 1].size() - colum % SIZE_OF_FUNCTIONS - 1)
                            / SIZE_OF_FUNCTIONS)]);
                }
            }
            clickFunctionNow->changePress();
        }
        else if (key == Qt::Key_S || key == 1067 || key == Qt::Key_Down) {
            if (row + 1 == vectorFunction.size() && vectorFunction[row].size() <= colum + SIZE_OF_FUNCTIONS) {
                if (vectorFunction[row].size() > colum + SIZE_OF_FUNCTIONS) {
                    function_Pressed(vectorFunction[row][colum + SIZE_OF_FUNCTIONS]);
                }
                else {
                    function_Pressed(vectorFunction[0][colum % SIZE_OF_FUNCTIONS]);
                }
            }
            else {
                if (vectorFunction[row].size() > colum + SIZE_OF_FUNCTIONS) {
                    function_Pressed(vectorFunction[row][colum + SIZE_OF_FUNCTIONS]);
                }
                else {
                    function_Pressed(vectorFunction[row + 1][colum % SIZE_OF_FUNCTIONS]);
                }
            }
            clickFunctionNow->changePress();
        }
        else if (key == Qt::Key_D || key == 1042 || key == Qt::Key_Right) {
            if (colum + 1 == vectorFunction[vectorFunction.size() - 1].size() && row + 1 == vectorFunction.size()) {
                function_Pressed(vectorFunction[0][0]);
            }
            else {
                if (colum + 1 == vectorFunction[clickFunctionNow->getRow()].size()) {
                    function_Pressed(vectorFunction[row + 1][0]);
                }
                else {
                    function_Pressed(vectorFunction[row][colum + 1]);
                }
            }
            clickFunctionNow->changePress();
        }
        else if (key == Qt::Key_A || key == 1060 || key == Qt::Key_Left) {
            if (colum == 0 && row == 0) {
                function_Pressed(vectorFunction[vectorFunction.size() - 1][vectorFunction[vectorFunction.size() - 1].size() - 1]);
            }
            else {
                if (colum == 0) {
                    colum = vectorFunction[row - 1].size() - 1;
                    function_Pressed(vectorFunction[row - 1][colum]);
                }
                else {
                    function_Pressed(vectorFunction[row][colum - 1]);
                }
            }
            clickFunctionNow->changePress();
        }
    }
}

void GameWindow::on_question_clicked() {
    QMessageBox::information(this, "Как играть в эту игру?", 
        "1) Чтобы пройти уровень нужно собрать все звезды, для этого нужно составить наборы команд для ракеты\n"
        "2) Если при выполнении команд ракета выходит за границы поля уровня игра прекращается. \n"
        "3) Команда, к которой будет добавлен цвет, будет выполняться только в том случае если ракета в тот момент будет находится на клетке такого же цвета\n"
        "4) Для выбора цвета и команды выделенной клетки нужно нажать левой кнопкой мыши на их значения в правой части экрана, при перемещении на следующую пустую клетку она автоматически заполняется значениями из предыдущей\n"
        "5) Если цвет или команда выбраны в данной клетке, то он отобразятся в ней и будут выделены темным контуром\n"
        "6) Перемещаться по наборам команд можно либо нажатием левой кнопки мыши, либо с помощью стрелок или клавиш WASD\n"
        "7) Чтобы убрать из клетки цвет или команду, выберите клетку и нажмите по команде или цвету еще раз\n");
}
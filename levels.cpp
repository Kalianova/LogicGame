#include "levels.h"
#include "ui_levels.h"
#include "map.h"
#include "gamewindow.h"
#include "createmap.h"
#include <QAction>


Levels::Levels(QWidget* parent) :
    QMainWindow(parent),
    parentWindow(parent),
    ui(new Ui::Levels)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    this->setWindowTitle("Уровни");
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    ui->graphicsView->resize(733, 463);
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);

    ui->graphicsView->setScene(scene);
    readLevels();
    drawLevels();

    dialog = new QFileDialog(this);

    connect(ui->create, SIGNAL(triggered()), this, SLOT(on_create_clicked()));
    connect(ui->download, SIGNAL(triggered()), this, SLOT(on_download_clicked()));
}

void Levels::readLevels(){
    pathsToLevel.clear();
    QFile qfile(QDir().currentPath()+"/map/config.txt");
    qfile.open(QFile::ReadOnly | QFile::Text);
    QString name;
    int solved;
    while(!qfile.atEnd()){
        QString s = qfile.readLine();
        solved = s[s.size()-2].digitValue();
        name = s.mid(0,s.size() - 3);
        Map validMap;
        validMap.ReadFrom(name);
        if (validMap.isValid()) {
            pathsToLevel.push_back(std::make_pair(name, solved));
        }
    }
    qfile.close();
    writeFile();
}

void Levels::drawLevels() {
    for (auto i : rects) {
        delete i;
    }
    rects.resize(0);
    scene->clear();
    for (size_t i = 0; i < pathsToLevel.size(); i++) {
        double size = scene->width() / SIZE_OF_LEVELS;
        ClickColor* clickcolor;
        if (pathsToLevel[i].second == 1) {
            clickcolor = new ClickColor(Qt::green, size, i);
        }
        else {
            clickcolor = new ClickColor(Qt::lightGray, size, i);
        }
        clickcolor->setPos(i % SIZE_OF_LEVELS * size + size / 2 + 2, i / SIZE_OF_LEVELS * size + size / 2 + 2);
        rects.push_back(clickcolor);
        QGraphicsTextItem* text = new QGraphicsTextItem(globals::nameOfLevelFromPath(pathsToLevel[i].first));
        text->setPos(-size/2 + 2, -size/2 + 5);
        text->setTextWidth(size - 2);
        text->setParentItem(clickcolor);
        scene->addItem(clickcolor);
        connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(level_Pressed(ClickColor*)));
    }
}

void Levels::openLevel(QString path) {
    GameWindow* window = new GameWindow(path, parentWindow);
    window->show();
    this->setVisible(false);
}

void Levels::writeFile() {
    QFile qfile(QDir().currentPath() + "/map/config.txt");
    qfile.open(QFile::WriteOnly);
    QTextStream writeStreamConfig(&qfile);
    writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
    for (size_t i = 0; i < pathsToLevel.size(); i++) {
        writeStreamConfig << pathsToLevel[i].first << " " << pathsToLevel[i].second << "\r\n";
    }
    qfile.close();
}

Levels::~Levels() {
    delete ui;
    delete scene;
    delete clicklevel;
    delete dialog;
}

void Levels::level_Pressed(ClickColor* level) {
    if (!moving) {
        if (level->isPressed()) {
            clicklevel = nullptr;
        }
        else {
            if (clicklevel != nullptr) {
                clicklevel->changePress();
            }
            clicklevel = level;
        }
    }
    else {
        int begin = clicklevel->getNumberColor();
        int end = level->getNumberColor();
        std::pair<QString, int>  pair = pathsToLevel[clicklevel->getNumberColor()];
        pathsToLevel.erase(pathsToLevel.begin() + clicklevel->getNumberColor());
        if (clicklevel->getNumberColor() > level->getNumberColor()) {
            pathsToLevel.insert(pathsToLevel.begin() + level->getNumberColor() + 1, pair);
        }
        else {
            pathsToLevel.insert(pathsToLevel.begin() + level->getNumberColor(), pair);
        }
        level->changePress();
        clicklevel->changePress();
        writeFile();
        moving = false;
        QPointF position;
        int index = level->getNumberColor() + 1;
        if (clicklevel->getNumberColor() > level->getNumberColor()) {
            position = rects[level->getNumberColor() + 1]->pos();
            for (size_t i = level->getNumberColor() + 1; i < clicklevel->getNumberColor(); i++) {
                rects[i]->setIndex(i + 1);
                rects[i]->setPos(rects[i + 1]->pos());
            }
        }
        else {
            position = rects[level->getNumberColor()]->pos();;
            for (size_t i = level->getNumberColor(); i > clicklevel->getNumberColor(); i--) {
                rects[i]->setIndex(i - 1);
                rects[i]->setPos(rects[i - 1]->pos());
            }
        }
        clicklevel->setPos(position);
        clicklevel->setIndex(index);
        clicklevel = nullptr;
    }
}

void Levels::on_exit_clicked() {
    parentWindow->setVisible(true);
    this->close();
}

void Levels::on_beginLevel_clicked() {
    if (clicklevel != nullptr) {
        openLevel(pathsToLevel[clicklevel->getNumberColor()].first);
        readLevels();
        drawLevels();
        clicklevel = nullptr;
    }
    else {
        QMessageBox::information(this, "Уровень не выбран", "Выберите уровень");
    }
}

void Levels::on_create_clicked() {
    CreateMap* window = new CreateMap(parentWindow);
    this->hide();
    window->show();
}

void Levels::on_download_clicked() {
    QString path = dialog->getOpenFileName(this, "Выберите уровень", QDir::currentPath() + "/map", tr("Text files(*.txt)"));  
    if (path != nullptr) {
        QFile qconfig(QDir().currentPath() + "/map/config.txt");
        for (size_t i = 0; i < pathsToLevel.size(); i++) {
            if (globals::nameOfLevelFromPath(pathsToLevel[i].first) == globals::nameOfLevelFromPath(path)) {
                QMessageBox::information(this, "Уровень уже существует", "Выберите другой файл");
                return;
            }
        }
        Map map;
        dialog->close();
        map.ReadFrom(path);
        if (map.isValid()) {
            qconfig.open(QFile::WriteOnly | QFile::Append);
            QTextStream writeStreamConfig(&qconfig);
            writeStreamConfig.setCodec("UTF-8");
            writeStreamConfig << path << " 0" << "\r\n";
            qconfig.close();
            readLevels();
            drawLevels();
        }
        else {
            QMessageBox::information(this, "Уровень не может быть добавлен", "Файл поврежден или составлен неверно");
        }
    }
}


void Levels::on_deleteLevel_clicked() {
    if (clicklevel != nullptr) {
        int n = QMessageBox::warning(this, "Удаление уровня", "Вы дествительно хотите удалить этот уровень?", "Да", "Нет", NULL, 0, 1);
        if (n == 0) {
            QFile qfile(QDir().currentPath() + "/map/config.txt");
            qfile.open(QFile::WriteOnly);
            QTextStream writeStreamConfig(&qfile);
            writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
            for (size_t i = 0; i < pathsToLevel.size(); i++) {
                if (i != clicklevel->getNumberColor()) {
                    writeStreamConfig << pathsToLevel[i].first << " " << pathsToLevel[i].second << "\r\n";
                }
            }
            qfile.close();
            readLevels();
            drawLevels();
            clicklevel = nullptr;
        }
    }
    else {
        QMessageBox::information(this, "Уровень не выбран", "Выберите уровень");
    }
}

void Levels::on_moveLevel_clicked() {
    if (clicklevel != nullptr) {
        QMessageBox::information(this, "Выберите уровень", "Выберите уровень, после которого хотите поместить выбранный ранее уровень");
        moving = true;
        int number = clicklevel->getNumberColor();
        readLevels();
        drawLevels();
        clicklevel = rects[number];
        clicklevel->changePress();
    }
    else {
        QMessageBox::information(this, "Уровень не выбран", "Выберите уровень");
    }
}

#include "createmap.h"
#include "ui_createmap.h"
#include <fstream>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <globals.h>
#include <QKeyEvent>


CreateMap::CreateMap(QWidget* parent) :
    QMainWindow(parent),
    parentWindow(parent),
    ui(new Ui::CreateMap)
{
    ui->setupUi(this);
    this->setWindowTitle("Создать карту");
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setCheckBoxColor(Qt::blue, ui->blue);
    setCheckBoxColor(Qt::red, ui->red);
    setCheckBoxColor(Qt::darkMagenta, ui->dark_magenta);
    setCheckBoxColor(Qt::darkYellow, ui->dark_yellow);
    createmap = new QGraphicsScene();
    createmap->setBackgroundBrush(Qt::gray);
    ui->graphicsView->resize(561, 511);
    ui->graphicsView->setScene(createmap);
    createmap->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);
    createScene();
}

CreateMap::~CreateMap() {
    delete ui;
    delete clickfunction;
    delete clickFunctionNow;
    delete player;
    delete createmap;
}

bool CreateMap::isUnique(QString name) {
    QFile qfile(QDir().currentPath() + "/map/config.txt");
    qfile.open(QFile::ReadOnly | QFile::Text);
    while (!qfile.atEnd()) {
        QString str = qfile.readLine();
        str = globals::nameOfLevelFromPath(str.mid(0, str.size() - 3));
        if (name == str) {
            return false;
        }
    }
    qfile.close();
    return true;
}

void CreateMap::setCheckBoxColor(QColor color, QCheckBox* checkbox) {
    QPixmap pix(47, 47);
    pix.fill(color);
    checkbox->setIcon(QIcon(pix));
    checkbox->setIconSize(QSize(47, 47));
}

void CreateMap::createScene() {
    double size = (this->ui->graphicsView->height()) / 10;
    double sizeOfRectMap = size * 10 / sizeOfMap;
    createColor(Qt::gray, size, 0);
    createColor(Qt::blue, size, 1);
    createColor(Qt::darkMagenta, size, 2);
    createColor(Qt::red, size, 3);
    createColor(Qt::darkYellow, size, 4);
    createImage(":/image/star", size, 5, 0);
    createImage(":/image/rocket", size, 6, 0);
    createImage(":/image/rocket", size, 7, 90);
    createImage(":/image/rocket", size, 8, 180);
    createImage(":/image/rocket", size, 9, 270);
    for (size_t i = 0; i < sizeOfMap; i++) {
        for (size_t j = 0; j < sizeOfMap; j++) {
            createFunction(i, j, sizeOfRectMap);
        }
    }
    clickcolor = nullptr;
    clickcommand = nullptr;
    clickfunction = nullptr;
}

void CreateMap::createColor(QColor color, double size, int count) {
    clickcolor = new ClickColor(color, size, count);
    clickcolor->setPos(size * 10 + size / 2,
        size / 2 + size * count);
    connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
    createmap->addItem(clickcolor);
}

void CreateMap::createImage(QString path, double size, int count, int rotation) {
    QPixmap image;
    image.load(path);
    clickcommand = new ClickCommand(image, size, count);
    clickcommand->setPos(size * 10 + size / 2,
        size / 2 + size * count);
    clickcommand->setRotation(rotation);
    connect(clickcommand, SIGNAL(commandChanged(ClickCommand*)), this, SLOT(image_Pressed(ClickCommand*)));
    createmap->addItem(clickcommand);
}

void CreateMap::createFunction(int row, int colum, double size) {
    clickfunction = new ClickFunction(size, row, colum);
    clickfunction->setPos(size * row + size / 2 - 2, size * colum + size / 2 - 2);
    createmap->addItem(clickfunction);
    connect(clickfunction, SIGNAL(rectangleChanged(ClickFunction*)), this, SLOT(rectangle_Pressed(ClickFunction*)));
    vectorfunctions.push_back(clickfunction);
}

void CreateMap::image_Pressed(ClickCommand* command) {
    if (clickcommand != nullptr) {
        clickcommand->changePress();
    }
    clickcommand = command;
    if (clickcolor != nullptr) {
        clickcolor->changePress();
        clickcolor = nullptr;
    }
}

void CreateMap::rectangle_Pressed(ClickFunction* function) {
    if (clickcommand != nullptr) {
        if (function->getColor() != nullptr) {
            if (function->getColor()->getColor() != Qt::gray) {
                if (clickcommand->getNumberCommand() > 5) {
                    if (player != nullptr) {
                        player->setCommand(nullptr);
                        player->update();
                    }
                    player = function;
                }
                function->setCommand(clickcommand);
                switch (function->getCommand()->getNumberCommand()) {
                case 7:
                    function->setRotation(90);
                    break;
                case 8:
                    function->setRotation(180);
                    break;
                case 9:
                    function->setRotation(270);
                    break;
                }
            }
            else {
                function->changePress();
            }
        }
        else {
            function->changePress();
        }
        clickFunctionNow = function;
    }
    if (clickcolor != nullptr) {
        if (clickcolor->getColor() == Qt::gray) {
            function->setColor(nullptr);
            function->setCommand(nullptr);
            clickFunctionNow = nullptr;
        }
        else {
            function->setColor(clickcolor);
            clickFunctionNow = function;
        }
    }
    if (function->getColor() == nullptr && clickcommand == nullptr) {
        function->changePress();
    }
    function->update();
}

void CreateMap::color_Pressed(ClickColor* color) {
    if (clickcolor != nullptr) {
        clickcolor->changePress();
    }
    clickcolor = color;
    if (clickcommand != nullptr) {
        clickcommand->changePress();
        clickcommand = nullptr;
    }
}

void CreateMap::on_sizeOfMap_valueChanged(int arg1) {
    sizeOfMap = arg1;
    createmap->clear();
    vectorfunctions.resize(0);
    player = nullptr;
    createScene();
}

void CreateMap::on_spinBoxFunction1_valueChanged(int arg1) {
    if (arg1 == 0) {
        ui->function1->setChecked(false);
    }
}

void CreateMap::on_spinBoxFunction2_valueChanged(int arg1) {
    if (arg1 == 0) {
        ui->function2->setChecked(false);
    }
}

void CreateMap::on_spinBoxFunction3_valueChanged(int arg1) {
    if (arg1 == 0) {
        ui->function3->setChecked(false);
    }
}

void CreateMap::on_spinBoxFunction4_valueChanged(int arg1) {
    if (arg1 == 0) {
        ui->function4->setChecked(false);
    }
}

void CreateMap::on_spinBoxFunction5_valueChanged(int arg1) {
    if (arg1 == 0) {
        ui->function5->setChecked(false);
    }
}

void CreateMap::on_function1_stateChanged(int arg1) {
    if (ui->function1->isChecked()) {
        ui->spinBoxFunction1->setValue(5);
    }
}

void CreateMap::on_function2_stateChanged(int arg1) {
    if (ui->function2->isChecked()) {
        ui->spinBoxFunction2->setValue(5);
    }
}

void CreateMap::on_function3_stateChanged(int arg1) {
    if (ui->function3->isChecked()) {
        ui->spinBoxFunction3->setValue(5);
    }
}

void CreateMap::on_function4_stateChanged(int arg1) {
    if (ui->function4->isChecked()) {
        ui->spinBoxFunction4->setValue(5);
    }
}

void CreateMap::on_function5_stateChanged(int arg1) {
    if (ui->function5->isChecked()) {
        ui->spinBoxFunction5->setValue(5);
    }
}

void CreateMap::on_cancel_clicked() {
    parentWindow->setVisible(true);
    this->close();
}

void CreateMap::on_create_clicked() {
    if (player == nullptr) {
        QMessageBox::information(this, "Игрок отсутствует", "Выберите положение игрока на поле");
    }
    else if (ui->name_level->text() == NULL) {
        QMessageBox::information(this, "Название отсутствует", "Выберите название уровня");
    }
    else if (!isUnique(ui->name_level->text())) {
        QMessageBox::information(this, "Неверное название", "Такое название уже используется. Выберите другое название уровня.");
    }
    else {       
        QDir* dir;
        QDir().mkdir("map");
        QFile qconfig(dir->currentPath() + "/map/config.txt");
        qconfig.open(QFile::WriteOnly | QFile::Append);
        QTextStream writeStreamConfig(&qconfig);
        writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
        writeStreamConfig << dir->currentPath() << "/map/" << ui->name_level->text() << ".txt 0" << "\r\n";
        qconfig.close();
        QFile qfile(dir->currentPath() + "/map/" + ui->name_level->text() + ".txt");
        qfile.open(QFile::WriteOnly | QFile::Text);
        QTextStream writeStream(&qfile);
        int sizeOfMap = ui->sizeOfMap->value();
        writeStream << sizeOfMap << "\n";
        int playerX{ 0 }, playerY{ 0 };
        for (size_t i = 0; i < sizeOfMap; i++) {
            for (size_t j = 0; j < sizeOfMap; j++) {
                int index = 0;
                if (vectorfunctions[j * sizeOfMap + i]->getCommand() != nullptr) {
                    index = vectorfunctions[j * sizeOfMap + i]->getCommand()->getNumberCommand();
                }
                if (index > 5) {
                    playerX = i;
                    playerY = j;
                    writeStream << vectorfunctions[j * sizeOfMap + i]->getFunction() - index;
                }
                else {
                    writeStream << vectorfunctions[j * sizeOfMap + i]->getFunction();
                }
            }
            writeStream << "\n";
        }
        writeStream << playerX << " " << playerY << " " <<
            (player->getCommand()->getNumberCommand() - 6) * 90 << "\n";
        QString commands;
        QString functions;
        QString colors;
        int count = 0;
        if (ui->arrow_up->isChecked()) {
            commands += " 1";
            count++;
        }
        if (ui->arrow_right->isChecked()) {
            commands += " 2";
            count++;
        }
        if (ui->arrow_left->isChecked()) {
            commands += " 3";
            count++;
        }
        if (ui->blue_brush->isChecked()) {
            commands += " 4";
            count++;
        }
        if (ui->dark_magenta_brush->isChecked()) {
            commands += " 5";
            count++;
        }
        if (ui->red_brush->isChecked()) {
            commands += " 6";
            count++;
        }
        if (ui->dark_yellow_brush->isChecked()) {
            commands += " 7";
            count++;
        }
        if (ui->function1->isChecked()) {
            commands += " 8";
            count++;
        }
        if (ui->function2->isChecked()) {
            commands += " 9";
            count++;
        }
        if (ui->function3->isChecked()) {
            commands += " 10";
            count++;
        }
        if (ui->function4->isChecked()) {
            commands += " 11";
            count++;
        }
        if (ui->function5->isChecked()) {
            commands += " 12";
            count++;
        }
        writeStream << count << "\n";
        writeStream << commands.remove(0, 1) << "\n";

        count = 0;
        if (ui->spinBoxFunction1->value() != 0) {
            functions += " " + QString::number(ui->spinBoxFunction1->value()) + "1";
            count++;
        }
        if (ui->spinBoxFunction2->value() != 0) {
            functions += " " + QString::number(ui->spinBoxFunction2->value()) + "2";
            count++;
        }
        if (ui->spinBoxFunction3->value() != 0) {
            functions += " " + QString::number(ui->spinBoxFunction3->value()) + "3";
            count++;
        }
        if (ui->spinBoxFunction4->value() != 0) {
            functions += " " + QString::number(ui->spinBoxFunction4->value()) + "4";
            count++;
        }
        if (ui->spinBoxFunction5->value() != 0) {
            functions += " " + QString::number(ui->spinBoxFunction5->value()) + "5";
            count++;
        }

        writeStream << count << "\n";
        writeStream << functions.remove(0, 1) << "\n";

        if (ui->blue->isChecked()) {
            colors += " 1";
        }
        if (ui->dark_magenta->isChecked()) {
            colors += " 2";
        }
        if (ui->red->isChecked()) {
            colors += " 3";
        }
        if (ui->dark_yellow->isChecked()) {
            colors += " 4";
        }
        writeStream << colors.length() / 2 << "\n";
        writeStream << colors.remove(0, 1);
        qfile.close();
        QMessageBox::information(this, "\"" + ui->name_level->text() + "\" добавлен", "Чтобы пройти созданный уровень выберите его в меню уровней");
        player = nullptr;
        createmap->clear();
        createScene();
    }
}

void CreateMap::on_howToCreate_clicked() {
    QMessageBox::information(this, "Как создать уровень", "1) Выберите размер карты\n"
        "2) Заполните карту цветами, звездами и расположите ракету\n"
        "3) Выберите нужные для прохождения уровня команды, цвета и функции\n"
        "4) Укажите название уровня\n"
        "5) Нажмите кнопку создать\n"
    );
}
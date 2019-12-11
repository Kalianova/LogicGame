#include "levels.h"
#include "ui_levels.h"
#include "map.h"
#include "gamewindow.h"
#include "string.h"
#include<iostream>
#include <exception>
#include <QDir>


levels::levels(QWidget* parent) :
	QMainWindow(parent),
	parentWindow(parent),
    ui(new Ui::levels)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
      this->setWindowTitle("Уровни");

	ui->graphicsView->resize(723, 403);
	scene->setSceneRect(0, 0, ui->graphicsView->width() - 4, ui->graphicsView->height() - 4);
    
	
    ui->graphicsView->setScene(scene);
    readLevels();
	drawLevels();

}

void levels::readLevels(){
    pathsToLevel.clear();
    QFile qfile(QDir().currentPath()+"/map/config.txt");
    qfile.open(QFile::ReadOnly | QFile::Text);

    QString name;
    int solved;
    while(!qfile.atEnd()){
        QString s = qfile.readLine();
        solved = s[s.size()-2].digitValue();
        name = s.mid(0,s.size() - 3);
        pathsToLevel.push_back(std::make_pair(name,solved));
    }
    qfile.close();
}

void levels::drawLevels()
{
    for(auto i: rects){
       delete i;
    }
 rects.resize(0);
 scene->clear();
	for (size_t i = 0; i < pathsToLevel.size(); i++)
	{
		double size = scene->width() / SIZE_OF_LEVELS;
        ClickColor* clickcolor;
		if (pathsToLevel[i].second == 1) {
            clickcolor = new ClickColor(Qt::green,size,i);

		}
		else {
              clickcolor = new ClickColor(Qt::lightGray,size,i);
		}
        std::string s= pathsToLevel[i].first.toStdString();
        clickcolor->setPos(i%SIZE_OF_LEVELS*size + size/2 + 2, i/ SIZE_OF_LEVELS * size + size/2+ 2);
            connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
         rects.push_back(clickcolor);
        QGraphicsTextItem* text = new QGraphicsTextItem(QString::fromStdString(s.substr(s.find_last_of('/') + 1, s.find_last_of('.') - s.find_last_of('/') - 1)));
        text->setPos(i % SIZE_OF_LEVELS * size + 4, i / SIZE_OF_LEVELS * size + 7);
        text->setTextWidth(size - 2);
        scene->addItem(clickcolor);
        scene->addItem(text);
	}
}

void levels::addLevel(QString path){
    while(path.contains('\\',Qt::CaseSensitive)){
       path.replace( path.indexOf('\\',Qt::CaseSensitive),1,'/');
}
    QFile qconfig(QDir().currentPath()+"/map/config.txt");
    if (QFile(QDir().currentPath()+"/map/config.txt").exists()) {
            for (size_t i = 0; i < pathsToLevel.size(); i++){
                if(pathsToLevel[i].first == path){
                    QMessageBox::information(this, "Файл уже существует","Проверьте путь к файлу");
                    return;
                         }
            }

            Map map;
            map.ReadFrom(path);
            if (map.isValid()) {
                qconfig.open(QFile::WriteOnly | QFile::Append);
                QTextStream writeStreamConfig(&qconfig);
                writeStreamConfig.setCodec("UTF-8");
                writeStreamConfig << path << " 0" <<"\r\n";
                qconfig.close();
                QMessageBox::information(this, "Успешно","Уровень добавлен в меню уровней");
                readLevels();

                drawLevels();
            }
            else {
                QMessageBox::information(this, "Файл не может быть добавлен","Файл поврежден или составлен неверно, проверьте путь и содержимое файла");
            }
	}
	else {
        QMessageBox::information(this, "Файл не существует", "Проверьте путь к файлу");
	}
}

void levels::openLevel(QString path)
{
    gamewindow* window = new gamewindow(path, parentWindow);
	window->show();
	this->setVisible(false);
}


levels::~levels()
{
    delete ui;
}

void levels::color_Pressed(ClickColor* color) {
if(color->isPressed()){
    clickcolor = nullptr;
}
else{
    if(clickcolor!=nullptr){
    clickcolor->changePress();
    }
    clickcolor = color;
}
}


void levels::on_add_clicked()
{
    if(ui->pathTolevel->text()== nullptr){
          QMessageBox::information(this, "Путь не введен","Введите путь к файлу");
    }
    else{
        addLevel(ui->pathTolevel->text());
    }
}

void levels::on_exit_clicked()
{
    parentWindow->setVisible(true);
    this->close();
}

void levels::on_begin_clicked()
{
if(clickcolor!=nullptr){
    openLevel(pathsToLevel[ clickcolor->getNumberColor()].first);
    readLevels();
    drawLevels();
    clickcolor = nullptr;
}
else{
      QMessageBox::information(this, "Уровень не выбран","Выберите уровень");
}
}


void levels::on_delete_2_clicked()
{
    if(clickcolor!=nullptr){
        QFile qfile(QDir().currentPath()+"/map/config.txt");
        qfile.open(QFile::WriteOnly);
        QTextStream writeStreamConfig(&qfile);
        writeStreamConfig.setCodec(QTextCodec::codecForName("UTF-8"));
             for (size_t i = 0; i < pathsToLevel.size(); i++){
                 if(i!=clickcolor->getNumberColor()){
                        writeStreamConfig <<pathsToLevel[i].first<<" " << pathsToLevel[i].second<<"\r\n" ;
                 }
             }
        qfile.close();
        readLevels();
        drawLevels();
        clickcolor = nullptr;
    }
    else{
       QMessageBox::information(this, "Уровень не выбран","Выберите уровень");
    }
}

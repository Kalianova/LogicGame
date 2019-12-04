#include "createmap.h"
#include "ui_createmap.h"

CreateMap::CreateMap(QWidget* parent) :
	QMainWindow(parent),
	parentWindow(parent),
    ui(new Ui::CreateMap)
{
    ui->setupUi(this);
	this->setWindowTitle("Create map");
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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
}

void CreateMap::setCheckBoxColor(QColor color, QCheckBox* checkbox) {
	QPixmap pix(47, 47);
	pix.fill(color);
	checkbox->setIcon(QIcon(pix));
	checkbox->setIconSize(QSize(47, 47));
}

void CreateMap::createScene() {
	double size = (this->ui->graphicsView->height()) / 10;
	double sizeOfRectMap = size*10/sizeOfMap;
	createColor(Qt::gray, size, 0);
	createColor(Qt::blue, size, 1);
	createColor(Qt::darkMagenta, size, 2);
	createColor(Qt::red, size, 3);
	createColor(Qt::darkYellow, size, 4);
	createImage(":/image/star",size, 5, 0);
	createImage(":/image/rocket", size, 6, 0);
	createImage(":/image/rocket", size, 7, 90);
	createImage(":/image/rocket", size, 8, 180);
	createImage(":/image/rocket", size, 9, 270);
	for (size_t i = 0; i < sizeOfMap; i++)
	{
		for (size_t j = 0; j < sizeOfMap; j++)
		{
			createFunction(i, j, sizeOfRectMap);
		}
	}
	clickcolor = nullptr;
	clickcommand = nullptr;
	clickfunction = nullptr;
}

void CreateMap::createColor(QColor color, double size, int count) {
	clickcolor = new ClickColor(color,size,count);
	clickcolor->setPos(size * 10 + size / 2,
		size / 2 + size * count);
	connect(clickcolor, SIGNAL(colorChanged(ClickColor*)), this, SLOT(color_Pressed(ClickColor*)));
	createmap->addItem(clickcolor);
}

void CreateMap::createImage(QString path, double size, int count, int rotation )
{
	QPixmap image;
	image.load(path);
	clickcommand = new ClickCommand(image,size,count);
	clickcommand->setPos(size * 10 + size / 2,
		size / 2 + size * count);
	clickcommand->setRotation(rotation);
	connect(clickcommand, SIGNAL(commandChanged(ClickCommand*)), this, SLOT(image_Pressed(ClickCommand*)));
	createmap->addItem(clickcommand);
}

void CreateMap::createFunction(int row, int colum, double size)
{
	clickfunction = new ClickFunction(size);
	clickfunction->setPos(size * row + size/2 - 2 , size * colum + size/2 - 2);
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
				if (clickcommand->getIndex() > 5) {
					if (player != nullptr) {
						player->setCommand(nullptr);
						player->update();
					}
					player = function;
				}
				function->setCommand(clickcommand);
				switch (function->getCommand()->getIndex()) {
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
	}
	if (clickcolor != nullptr) {
		if (clickcolor->getColor() == Qt::gray) {
			function->setColor(nullptr);
		}
		else {
			function->setColor(clickcolor);
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

void CreateMap::on_spinBox_valueChanged(int arg1) {
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
	//�������� ����������
	//��������� ������� ����� �� �����
}

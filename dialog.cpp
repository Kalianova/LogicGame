#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
 

}

Dialog::Dialog(QString label, QString button, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	this->setWindow(label, button);
}

void Dialog::setWindow(QString label, QString button)
{
	ui->label->setText(label);
	ui->pushButton->setText(button);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
	this->hide();
	emit button_pushed();
}

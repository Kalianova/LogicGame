#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

//#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
	explicit Dialog(QString, QString, QWidget* parent = nullptr);
	void setWindow(QString, QString);
    ~Dialog();
signals:
	void button_pushed();
private slots:

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

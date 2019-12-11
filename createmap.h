#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <QMainWindow>
#include<QCheckBox>
#include <QGraphicsScene>
#include<click.h>
#include<vector>

namespace Ui {
class CreateMap;
}

class CreateMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateMap(QWidget *parent = nullptr);
    ~CreateMap();

private:
    Ui::CreateMap *ui;
    QGraphicsScene* createmap;
    QWidget* parentWindow;
    bool isUnique(QString);
    void setCheckBoxColor(QColor, QCheckBox*);
    void createScene();
    void createColor(QColor,double, int);
    void createImage(QString, double, int, int);
    void createFunction(int, int, double);
    int sizeOfMap{ 10 };
    void keyPressed(ClickFunction* before, ClickFunction* now);
    ClickColor* clickcolor;
    ClickCommand* clickcommand;
    ClickFunction* clickfunction;
    ClickFunction* clickFunctionNow{ nullptr };
    ClickFunction* player{ nullptr };
    std::vector<ClickFunction*> vectorfunctions;
private slots:
    void color_Pressed(ClickColor*);
    void image_Pressed(ClickCommand*);
    void rectangle_Pressed(ClickFunction*);
    void on_sizeOfMap_valueChanged(int arg1);
    void on_spinBoxFunction1_valueChanged(int arg1);
    void on_spinBoxFunction2_valueChanged(int arg1);
    void on_spinBoxFunction3_valueChanged(int arg1);
    void on_spinBoxFunction4_valueChanged(int arg1);
    void on_spinBoxFunction5_valueChanged(int arg1);
    void on_function1_stateChanged(int arg1);
    void on_function2_stateChanged(int arg1);
    void on_function3_stateChanged(int arg1);
    void on_function4_stateChanged(int arg1);
    void on_function5_stateChanged(int arg1);
    void on_cancel_clicked();
    void on_create_clicked();
    void on_howToCreate_clicked();
protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // CREATEMAP_H

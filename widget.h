#ifndef WIDGET_H
#define WIDGET_H
#include"dialog.h"
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    Dialog dialog;

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void func();
    void on_lineEdit_2_textEdited(const QString &arg1);
    void on_pushButton_clicked();
};

#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <background.h>
#include <QGraphicsView>

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
    backGround *backgroundWithBox;
    QGraphicsScene *mainScene;
};

#endif // WIDGET_H

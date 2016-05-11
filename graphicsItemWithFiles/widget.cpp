#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mainScene = new QGraphicsScene(this);
    mainScene->setSceneRect(0, 0, 640, 480);
    QPixmap map = QPixmap(640, 480);
    map.fill(QColor(233, 233, 233));
    backgroundWithBox = new backGround(map);
    mainScene->addItem(backgroundWithBox);
    QGraphicsView *view = new QGraphicsView(mainScene, this);
    view->setGeometry(40, 30, 700, 500);
    connect(backgroundWithBox, SIGNAL(newItem(QRectF)), this, SLOT(newFileItem(QRectF)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newFileItem(const QRectF &bounding)
{
    item = new fileItem(bounding);
    mainScene->addItem(item);
}

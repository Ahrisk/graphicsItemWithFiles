#include "widget.h"
#include "ui_widget.h"
#define MINIMUMSIZE  30

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    sceneWidth = 640;
    sceneHeight = 480;
    setWindowState(Qt::WindowMaximized);
    dataBase.clear();
    mainScene = new QGraphicsScene(this);
    mainScene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    QPixmap map = QPixmap(sceneWidth, sceneHeight);
    map.fill(QColor(233, 233, 233));
    backgroundWithBox = new backGround(sceneWidth, sceneHeight, map);
    mainScene->addItem(backgroundWithBox);
    QGraphicsView *view = new QGraphicsView(mainScene, this);
    view->setGeometry(40, 30, sceneWidth + 20, sceneHeight + 15);
    connect(backgroundWithBox, SIGNAL(newItem(QRectF)), this, SLOT(newFileItem(QRectF)));
    item = NULL;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newFileItem(const QRectF &bounding)
{
    if ((bounding.width() < MINIMUMSIZE) || (bounding.height() < MINIMUMSIZE))
        return;
    for (int i = 1; ; i ++)
        if (! dataBase.contains(i))
        {
            item = new fileItem(i, sceneWidth, sceneHeight, bounding);
            dataBase.insert(i, item);
            mainScene->addItem(item);
            connect(item, SIGNAL(shutMe(fileItem*)), this, SLOT(shutAnItem(fileItem*)), Qt::QueuedConnection);
            connect(item, SIGNAL(setMe(fileItem*)), this, SLOT(settingForItem(fileItem*)));
            break;
        }
}

void Widget::shutAnItem(fileItem *goDie)
{
    int GD = goDie->getID();
    if (dataBase.contains(GD))
    {
        mainScene->removeItem(goDie);
        dataBase.remove(GD);
        delete goDie;
    }
}

void Widget::settingForItem(fileItem *anItem)
{
    settingDialog *stDialog = new settingDialog(this);
    connect(stDialog, SIGNAL(info(qreal,qreal,qreal,qreal)), anItem, SLOT(setRectSlot(qreal,qreal,qreal,qreal)));
    connect(stDialog, SIGNAL(file(QString)), anItem, SLOT(setFileString(QString)));
    connect(stDialog, SIGNAL(shutMe(settingDialog*)), this, SLOT(shutAWindow(settingDialog*)), Qt::QueuedConnection);
    stDialog->setID(anItem->getID());
    stDialog->setInfo(anItem->getRect().x(), anItem->getRect().y(), anItem->getRect().width(), anItem->getRect().height());
    stDialog->setFile(anItem->getFileString());
    stDialog->show();
}

void Widget::shutAWindow(settingDialog *goDie)
{
    if (goDie)
    {
        delete goDie;
    }
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "background.h"
#include "fileitem.h"
#include "settingdialog.h"
#include <QGraphicsView>
#include <QHash>

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
    fileItem *item;
    QGraphicsScene *mainScene;
    QHash<int, fileItem*> dataBase;
    int sceneWidth, sceneHeight;

private slots:
    void newFileItem(const QRectF &bounding);
    void shutAnItem(fileItem *goDie);
    void settingForItem(fileItem *anItem);
    void shutAWindow(settingDialog *goDie);
};

#endif // WIDGET_H

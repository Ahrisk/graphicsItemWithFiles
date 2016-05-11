﻿#ifndef FILEITEM
#define FILEITEM

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QHoverEvent>

class fileItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

signals:
    void shutMe(fileItem *);

public:
    fileItem(QGraphicsItem *parent = 0);
    fileItem(const QRectF &bounding, QGraphicsItem *parent = 0);
    virtual ~fileItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF rectBound;
};

#endif // FILEITEM


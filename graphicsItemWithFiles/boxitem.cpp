#include "boxitem.h"

boxItem::boxItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{}

QRectF boxItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(rectBound.left() - penWidth / 2,
                  rectBound.top() - penWidth / 2,
                  rectBound.width() + penWidth,
                  rectBound.height() + penWidth);
}

void boxItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setBrush(Qt::black);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLine(rectBound.topLeft(), rectBound.bottomLeft());
    painter->drawLine(rectBound.topLeft(), rectBound.topRight());
    painter->drawLine(rectBound.topRight(), rectBound.bottomRight());
    painter->drawLine(rectBound.bottomLeft(), rectBound.bottomRight());
}

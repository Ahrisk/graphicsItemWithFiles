#include "fileitem.h"

fileItem::fileItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    rectBound = QRectF(0, 0, 0, 0);
    this->setSelected(true);
    this->setZValue(1);
//    setAcceptDrops(true);
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    curse = new QCursor;
}

//the position info is contained in bounding
fileItem::fileItem(const QRectF &bounding, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    rectBound = QRectF(QPointF(0, 0), QSizeF(bounding.size()));
    this->setPos(bounding.topLeft());
    this->setSelected(true);
    this->setZValue(1);
//    this->setAcceptDrops(true);
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    curse = new QCursor;
}

fileItem::~fileItem()
{
    if (curse)
    {
        delete curse;
        curse = NULL;
    }
}

QRectF fileItem::boundingRect() const
{
    qreal penWidth = 5;
    return QRectF(rectBound.left() - penWidth / 2,
                  rectBound.top() - penWidth / 2,
                  rectBound.width() + penWidth,
                  rectBound.height() + penWidth);
}

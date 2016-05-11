#include "fileitem.h"
#include <QPen>
#include <QPainter>

fileItem::fileItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    rectBound = QRectF(0, 0, 0, 0);
    this->setSelected(true);
    this->setZValue(1);
//    setAcceptDrops(true);
    this->setFlags(ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    curse = new QCursor;
    cancel = NULL;
    settings = NULL;
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
    QPixmap cancelMap, settingsMap;
    cancelMap.load(":/new/prefix1/cancel");
    cancelMap = cancelMap.scaled(15, 15, Qt::IgnoreAspectRatio);
    cancel = new QGraphicsPixmapItem(cancelMap, this);
    cancel->setPos(rectBound.width() - 15, 0);
    settingsMap.load(":/new/prefix1/setting");
    settingsMap = settingsMap.scaled(15, 15, Qt::IgnoreAspectRatio);
    settings = new QGraphicsPixmapItem(settingsMap, this);
    settings->setPos(rectBound.width() - 30, 0);
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

void fileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(0, 255, 255, 80)));
    painter->drawRect(rectBound);
}

void fileItem::setRect(const QRectF &bounding)
{
    if (! cancel && ! settings)
    {
        QPixmap cancelMap, settingsMap;
        cancelMap.load(":/new/prefix1/cancel");
        cancelMap = cancelMap.scaled(15, 15, Qt::IgnoreAspectRatio);
        cancel = new QGraphicsPixmapItem(cancelMap, this);
        settingsMap.load(":/new/prefix1/setting");
        settingsMap = settingsMap.scaled(15, 15, Qt::IgnoreAspectRatio);
        settings = new QGraphicsPixmapItem(settingsMap, this);
    }
    this->setPos(bounding.topLeft());
    rectBound = QRectF(QPointF(0, 0), bounding.size());
    cancel->setPos(rectBound.width() - 15, 0);
    settings->setPos(rectBound.width() - 30, 0);
    update(boundingRect());
}

void fileItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF mousePoint = event->scenePos();
    QPointF rectTopLeft = this->scenePos() + rectBound.topLeft();
    QPointF rectBottomRight = this->scenePos() + rectBound.bottomRight();
    if ((rectTopLeft.x() - mousePoint.x() <= 3) && (mousePoint.x() - rectTopLeft.x() <= 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
    }
}

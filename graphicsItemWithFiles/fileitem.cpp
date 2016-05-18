#include "fileitem.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#define NODIRECTION   0
#define LEFTTOP       1
#define TOP           2
#define RIGHTTOP      3
#define RIGHT         4
#define RIGHTBOTTOM   5
#define BOTTOM        6
#define LEFTBOTTOM    7
#define LEFT          8
#define KILLDIRECTION 9
#define SETDIRECTION  10
#define MINIMUMSIZE   30
#define MAX2(a,b) ((a)>(b)?(a):(b))
#define MIN2(a,b) ((a)<(b)?(a):(b))

fileItem::fileItem(const int &ID, const int &sceneWidth, const int &sceneHeight, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->ID = ID;
    rectBound = QRectF(0, 0, 0, 0);
    this->setSelected(true);
//    this->setZValue(1);
    setAcceptDrops(true);
    this->setActive(true);
    this->setFlags(ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    curse = new QCursor;
    cancel = NULL;
    settings = NULL;
    scaleDirection = NODIRECTION;
    funnyTag = true;
    endingPoint = startPoint = QPointF(0, 0);
    pathString = "";
    this->sceneWidth = sceneWidth;
    this->sceneHeight = sceneHeight;
}

//the position info is contained in bounding
fileItem::fileItem(const int &ID, const int &sceneWidth, const int &sceneHeight, const QRectF &bounding, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->ID = ID;
    rectBound = QRectF(QPointF(0, 0), QSizeF(bounding.size()));
    this->setPos(bounding.topLeft());
    this->setSelected(true);
//    this->setZValue(1);
    this->setAcceptDrops(true);
    this->setActive(true);
    this->setFlags(ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
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
    scaleDirection = NODIRECTION;
    funnyTag = true;
    endingPoint = startPoint = QPointF(0, 0);
    pathString = "";
    this->sceneWidth = sceneWidth;
    this->sceneHeight = sceneHeight;
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
//    painter->setFont(QFont("Times" , 8));
    painter->drawText(rectBound, Qt::AlignLeft | Qt::AlignBottom, " " + pathString);
}

QPainterPath fileItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
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
    rectBound = QRectF(QPointF(0, 0), bounding.size());
    cancel->setPos(rectBound.width() - 15, 0);
    settings->setPos(rectBound.width() - 30, 0);
    this->setPos(bounding.left(), bounding.top());
    this->scene()->update();
}

void fileItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF mousePoint = event->scenePos();
    QPointF rectTopLeft = this->scenePos() + rectBound.topLeft();
    QPointF rectBottomRight = this->scenePos() + rectBound.bottomRight();
    if ((rectTopLeft.x() - mousePoint.x() <= 3) && (mousePoint.x() - rectTopLeft.x() <= 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeFDiagCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeBDiagCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeHorCursor);
    }
    else if ((rectBottomRight.x() - mousePoint.x() <= 3) && (mousePoint.x() - rectBottomRight.x() <= 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeBDiagCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeFDiagCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeHorCursor);
    }
    else if ((mousePoint.x() >= rectTopLeft.x() + 3) && (mousePoint.x() <= rectBottomRight.x() - 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeVerCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeVerCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeAllCursor);
    }
    if ((mousePoint.x() <= rectBottomRight.x()) && (mousePoint.x() >= rectBottomRight.x() - 30) && (mousePoint.y() >= rectTopLeft.y()) && (mousePoint.y() <= rectTopLeft.y() + 15))
        curse->setShape(Qt::PointingHandCursor);
    this->setCursor(*curse);
    update(boundingRect());
    QGraphicsItem::hoverEnterEvent(event);
}

void fileItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF mousePoint = event->scenePos();
    QPointF rectTopLeft = this->scenePos() + rectBound.topLeft();
    QPointF rectBottomRight = this->scenePos() + rectBound.bottomRight();
    if ((rectTopLeft.x() - mousePoint.x() <= 3) && (mousePoint.x() - rectTopLeft.x() <= 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeFDiagCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeBDiagCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeHorCursor);
    }
    else if ((rectBottomRight.x() - mousePoint.x() <= 3) && (mousePoint.x() - rectBottomRight.x() <= 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeBDiagCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeFDiagCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeHorCursor);
    }
    else if ((mousePoint.x() >= rectTopLeft.x() + 3) && (mousePoint.x() <= rectBottomRight.x() - 3))
    {
        if ((rectTopLeft.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectTopLeft.y() <= 3))
            curse->setShape(Qt::SizeVerCursor);
        else if ((rectBottomRight.y() - mousePoint.y() <= 3) && (mousePoint.y() - rectBottomRight.y() <= 3))
            curse->setShape(Qt::SizeVerCursor);
        else if ((mousePoint.y() <= rectBottomRight.y() - 3) && (mousePoint.y() >= rectTopLeft.y() + 3))
            curse->setShape(Qt::SizeAllCursor);
    }
    if ((mousePoint.x() <= rectBottomRight.x()) && (mousePoint.x() >= rectBottomRight.x() - 30) && (mousePoint.y() >= rectTopLeft.y()) && (mousePoint.y() <= rectTopLeft.y() + 15))
        curse->setShape(Qt::PointingHandCursor);
    this->setCursor(*curse);
    update(boundingRect());
    QGraphicsItem::hoverEnterEvent(event);
}

void fileItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    curse->setShape(Qt::ArrowCursor);
    this->setCursor(*curse);
    update(boundingRect());
    QGraphicsItem::hoverLeaveEvent(event);
}

void fileItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPoint = event->scenePos();
        QPointF rectStart = this->scenePos() + rectBound.topLeft();
        QPointF rectEnd = this->scenePos() + rectBound.bottomRight();
        if ((startPoint.x() - rectStart.x() <= 3) && (rectStart.x() - startPoint.x() <= 3))
        {
            if ((startPoint.y() - rectStart.y() <= 3) && (rectStart.y() - startPoint.y() <= 3))
            {
                scaleDirection = LEFTTOP;
                deltaImp = startPoint - rectStart;
                fixedPoint = rectEnd;
            }
            else if ((startPoint.y() - rectEnd.y() <= 3) && (rectEnd.y() - startPoint.y() <= 3))
            {
                scaleDirection = LEFTBOTTOM;
                deltaImp = startPoint - (this->scenePos() + rectBound.bottomLeft());
                fixedPoint = QPoint(rectEnd.x(), rectStart.y());
            }
            else if ((startPoint.y() >= rectStart.y() + 3) && (startPoint.y() <= rectEnd.y() - 3))
            {
                scaleDirection = LEFT;
                deltaImp = QPointF(startPoint.x() - rectStart.x(), 0);
                fixedPoint = QPoint(rectEnd.x(), 0);
            }
        }
        else if ((startPoint.x() - rectEnd.x() <= 3) && (rectEnd.x() - startPoint.x() <= 3))
        {
            if ((startPoint.y() - rectStart.y() <= 3) && (rectStart.y() - startPoint.y() <= 3))
            {
                scaleDirection = RIGHTTOP;
                deltaImp = startPoint - (this->scenePos() + rectBound.topRight());
                fixedPoint = QPoint(rectStart.x(), rectEnd.y());
            }
            else if ((startPoint.y() - rectEnd.y() <= 3) && (rectEnd.y() - startPoint.y() <= 3))
            {
                scaleDirection = RIGHTBOTTOM;
                deltaImp = startPoint - rectEnd;
                fixedPoint = rectStart;
            }
            else if ((startPoint.y() >= rectStart.y() + 3) && (startPoint.y() <= rectEnd.y() - 3))
            {
                scaleDirection = RIGHT;
                deltaImp = QPointF(startPoint.x() - rectEnd.x(), 0);
                fixedPoint = QPointF(rectStart.x(), 0);
            }
        }
        else if ((startPoint.x() >= rectStart.x() + 3) && (startPoint.x() <= rectEnd.x() - 3))
        {
            if ((startPoint.y() - rectStart.y() <= 3) && (rectStart.y() - startPoint.y() <= 3))
            {
                scaleDirection = TOP;
                deltaImp = QPointF(0, startPoint.y() - rectStart.y());
                fixedPoint = QPointF(0, rectEnd.y());
            }
            else if ((startPoint.y() - rectEnd.y() <= 3) && (rectEnd.y() - startPoint.y() <= 3))
            {
                scaleDirection = BOTTOM;
                deltaImp = QPointF(0, startPoint.y() - rectEnd.y());
                fixedPoint = QPointF(0, rectStart.y());
            }
            else if ((startPoint.y() >= rectStart.y() + 3) && (startPoint.y() <= rectEnd.y() - 3))
            {
                scaleDirection = NODIRECTION;
                deltaImp = startPoint - rectStart;
                fixedPoint = QPointF(rectBound.width(), rectBound.height());
            }
        }
        if ((startPoint.x() <= rectEnd.x()) && (startPoint.x() >= rectEnd.x() - 15) && (startPoint.y() >= rectStart.y()) && (startPoint.y() <= rectStart.y() + 15))
        {
            scaleDirection = KILLDIRECTION;
        }
        else if ((startPoint.x() < rectEnd.x() - 15) && (startPoint.x() >= rectEnd.x() - 30) && (startPoint.y() >= rectStart.y()) && (startPoint.y() <= rectStart.y() + 15))
        {
            scaleDirection = SETDIRECTION;
        }
        update(boundingRect());
    }
    else QGraphicsItem::mousePressEvent(event);
}

void fileItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        endingPoint = event->scenePos();
        QPointF movingPoint;
        movingPoint = endingPoint - deltaImp;
        startPoint = endingPoint;
        switch (scaleDirection)
        {
        case LEFTTOP:
        {
            qreal tempX = MAX2(0, MIN2(movingPoint.x(), fixedPoint.x() - MINIMUMSIZE));
            qreal tempY = MAX2(0, MIN2(movingPoint.y(), fixedPoint.y() - MINIMUMSIZE));
            qreal tempWidth = MIN2(fixedPoint.x(), MAX2(fixedPoint.x() - movingPoint.x(), MINIMUMSIZE));
            qreal tempHeight = MIN2(fixedPoint.y(), MAX2(fixedPoint.y() - movingPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case TOP:
        {
            qreal tempX = this->scenePos().x();
            qreal tempY = MAX2(0, MIN2(movingPoint.y(), fixedPoint.y() - MINIMUMSIZE));
            qreal tempWidth = rectBound.width();
            qreal tempHeight = MIN2(fixedPoint.y(), MAX2(fixedPoint.y() - movingPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case RIGHTTOP:
        {
            qreal tempX = this->scenePos().x();
            qreal tempY = MAX2(0, MIN2(movingPoint.y(), fixedPoint.y() - MINIMUMSIZE));
            qreal tempWidth = MIN2(sceneWidth - tempX, MAX2(movingPoint.x() - fixedPoint.x(), MINIMUMSIZE));
            qreal tempHeight = MIN2(fixedPoint.y(), MAX2(fixedPoint.y() - movingPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case RIGHT:
        {
            qreal tempX = this->scenePos().x();
            qreal tempY = this->scenePos().y();
            qreal tempWidth = MIN2(sceneWidth - tempX, MAX2(movingPoint.x() - fixedPoint.x(), MINIMUMSIZE));
            qreal tempHeight = rectBound.height();
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case RIGHTBOTTOM:
        {
            qreal tempX = this->scenePos().x();
            qreal tempY = this->scenePos().y();
            qreal tempWidth = MIN2(sceneWidth - tempX, MAX2(movingPoint.x() - fixedPoint.x(), MINIMUMSIZE));
            qreal tempHeight = MIN2(sceneHeight - tempY, MAX2(movingPoint.y()- fixedPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case BOTTOM:
        {
            qreal tempX = this->scenePos().x();
            qreal tempY = this->scenePos().y();
            qreal tempWidth = rectBound.width();
            qreal tempHeight = MIN2(sceneHeight - tempY, MAX2(movingPoint.y()- fixedPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case LEFTBOTTOM:
        {
            qreal tempX = MAX2(0, MIN2(movingPoint.x(), fixedPoint.x() - MINIMUMSIZE));
            qreal tempY = this->scenePos().y();
            qreal tempWidth = MIN2(fixedPoint.x(), MAX2(fixedPoint.x() - movingPoint.x(), MINIMUMSIZE));
            qreal tempHeight = MIN2(sceneHeight - tempY, MAX2(movingPoint.y()- fixedPoint.y(), MINIMUMSIZE));
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case LEFT:
        {
            qreal tempX = MAX2(0, MIN2(movingPoint.x(), fixedPoint.x() - MINIMUMSIZE));
            qreal tempY = this->scenePos().y();
            qreal tempWidth = MIN2(fixedPoint.x(), MAX2(fixedPoint.x() - movingPoint.x(), MINIMUMSIZE));
            qreal tempHeight = rectBound.height();
            this->setRect(QRectF(tempX, tempY, tempWidth, tempHeight));
            break;
        }
        case NODIRECTION:
        {
            //当时为什么要这么写。。但是现在看不明白也不好改了
            if ((movingPoint.x() != (endingPoint - deltaImp).x()) || (movingPoint.y() != (endingPoint - deltaImp).y()))
            {
                this->setPos(MAX2(0, MIN2(movingPoint.x(), sceneWidth - fixedPoint.x())), MAX2(0, MIN2(movingPoint.y(), sceneHeight - fixedPoint.y())));
            }
            else
            {
                QPointF movingEndPoint = endingPoint - deltaImp + fixedPoint;
                this->setPos(MAX2(0, MIN2(movingEndPoint.x() - fixedPoint.x(), sceneWidth - fixedPoint.x())), MAX2(0, MIN2(movingEndPoint.y() - fixedPoint.y(), sceneHeight - fixedPoint.y())));
            }
            break;
        }
        case KILLDIRECTION:
        {
            break;
        }
        case SETDIRECTION:
        {
            break;
        }
        }
        //从没有想过这个可以写的如此粗暴。。
        this->scene()->update();
    }
    else QGraphicsItem::mouseMoveEvent(event);
}

void fileItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    endingPoint = event->scenePos();
    QPointF rectStart = this->scenePos() + rectBound.topLeft();
    QPointF rectEnd = this->scenePos() + rectBound.bottomRight();
    if (event->button() == Qt::LeftButton)
    {
        //这儿做的非常委屈。。本意是想发出信号让GraphicsScene来remove这个item，但由于不知道发出信号的对象，所以没法connect，只能在内部处理，导致无法delete。。好臃肿。。
        if ((scaleDirection == KILLDIRECTION) && (endingPoint.x() <= rectEnd.x()) && (endingPoint.x() >= rectEnd.x() - 15) && (endingPoint.y() >= rectStart.y()) && (endingPoint.y() <= rectStart.y() + 15))
        {
            //this->setVisible(false);
            emit(shutMe(this));
        }
        else if ((scaleDirection == SETDIRECTION) && (endingPoint.x() < rectEnd.x() - 15) && (endingPoint.x() >= rectEnd.x() - 30) && (endingPoint.y() >= rectStart.y()) && (endingPoint.y() <= rectStart.y() + 15))
        {
            emit(setMe(this));
        }
        scaleDirection = NODIRECTION;
//      虽然是特别丑陋的，不管不顾的写法，但是。。我怂了你随意
        this->setPos(this->x() + 1, this->y() + 1);
        this->setPos(this->x() - 1, this->y() - 1);
        this->scene()->update();
    }
    else QGraphicsItem::mouseReleaseEvent(event);
}

void fileItem::setRectSlot(const qreal &x, const qreal &y, const qreal &width, const qreal &height)
{
    if ((x >= 0) && (y >= 0) && (x + width < sceneWidth) && (y + height < sceneHeight))
        setRect(QRectF(x, y, width, height));
    else
    {
        //error...
    }
}

void fileItem::setFileString(const QString &tempString)
{
    if (1) //something to be confirmed..
        pathString = tempString;
}

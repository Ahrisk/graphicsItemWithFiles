#ifndef FILEITEM
#define FILEITEM

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QHoverEvent>
#include <QCursor>

class fileItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

signals:
    void shutMe(fileItem *);
    void setMe(fileItem *);

public:
    fileItem(const int &ID, const int &sceneWidth, const int &sceneHeight, QGraphicsItem *parent = 0);
    fileItem(const int &ID, const int &sceneWidth, const int &sceneHeight, const QRectF &bounding, QGraphicsItem *parent = 0);
    virtual ~fileItem();
    void setRect(const QRectF &bounding);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getID() { return ID; }
    QRectF getRect() { return QRectF(this->pos(), rectBound.size()); }
    QString getFileString() { return pathString; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF rectBound;
    QCursor *curse; 
    QGraphicsPixmapItem *cancel, *settings; 
    QPointF startPoint, endingPoint, deltaImp, fixedPoint;
    QString pathString;
    int scaleDirection, ID, sceneWidth, sceneHeight;
    bool funnyTag;

private slots:
    void setRectSlot(const qreal &x, const qreal &y, const qreal &width, const qreal &height);
    void setFileString(const QString &tempString);

};

#endif // FILEITEM


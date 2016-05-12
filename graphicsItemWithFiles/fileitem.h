#ifndef FILEITEM
#define FILEITEM

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QHoverEvent>
#include <QCursor>

class fileItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

signals:
    void shutMe(fileItem *);

public:
    fileItem(QGraphicsItem *parent = 0);
    fileItem(const QRectF &bounding, QGraphicsItem *parent = 0);
    virtual ~fileItem();
    void setRect(const QRectF &bounding);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QRectF rectBound;
    QCursor *curse; 
    QGraphicsPixmapItem *cancel, *settings; 
};

#endif // FILEITEM


#ifndef BACKGROUND
#define BACKGROUND
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPixmap>
#include "boxitem.h"

class backGround : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    backGround(QGraphicsItem *parent = 0);
    backGround(const QPixmap &pix, QGraphicsItem *parent = 0);
    virtual ~backGround();
    void setBackground(const QImage &sourceImage);
    void setBackground(const QPixmap &sourceMap);

signals:
    void newItem(const QRectF &posInfo);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
//    inline void rectSelected(const QRectF &region);
//    inline void rectCleared();
    QPointF startPoint, endingPoint;
    boxItem *box;
    bool funnyTag;
};
#endif // BACKGROUND


#ifndef BOXITEM
#define BOXITEM
#include <QGraphicsItem>
#include <QPainter>

class boxItem : public QGraphicsItem
{
public:
    boxItem(QGraphicsItem *parent = 0);
    virtual ~boxItem(){}
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setBounding(const QRectF rectBound){this->rectBound = rectBound; update(boundingRect()); }

private:
    QRectF rectBound;
};

#endif // BOXITEM

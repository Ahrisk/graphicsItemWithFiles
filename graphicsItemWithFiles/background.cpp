﻿#include "background.h"
#include <QDebug>
#define MAX2(a,b)      (((a)>(b))?(a):(b))
#define MIN2(a,b)      (((a)<(b))?(a):(b))
#define GETPOS(a,b)    QPointF(MIN2((a).x(),(b).x()),MIN2((a).y(),(b).y()))
#define GETSIZE(a,b)   QSizeF(MAX2((a).x(),(b).x())-MIN2((a).x(),(b).x()),MAX2((a).y(),(b).y())-MIN2((a).y(),(b).y()))

backGround::backGround(const int &sceneWidth, const int &sceneHeight, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    box = NULL;
    funnyTag = false;
    startPoint = QPointF(0, 0);
    endingPoint = QPointF(0, 0);
    this->sceneWidth = sceneWidth;
    this->sceneHeight = sceneHeight;
}

backGround::backGround(const int &sceneWidth, const int &sceneHeight, const QPixmap &pix, QGraphicsItem *parent) : QGraphicsPixmapItem(pix, parent)
{
    box = NULL;
    funnyTag = true;
    startPoint = QPointF(0, 0);
    endingPoint = QPointF(0, 0);
    this->sceneWidth = sceneWidth;
    this->sceneHeight = sceneHeight;
}

backGround::~backGround()
{
    box = new boxItem(this);
}

void backGround::setBackground(const QPixmap &sourceMap)
{
    QGraphicsPixmapItem::setPixmap(sourceMap);
}

void backGround::setBackground(const QImage &sourceImage)
{
    QPixmap pix = QPixmap::fromImage(sourceImage);
    QGraphicsPixmapItem::setPixmap(pix);
}

void backGround::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPoint = event->pos();
        endingPoint = startPoint;
        box = new boxItem(this);
        box->setPos(startPoint);
        box->setBounding(QRectF(0, 0, 0, 0));
    }
    else
        QGraphicsPixmapItem::mousePressEvent(event);
}

void backGround::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        endingPoint = event->pos();
        endingPoint = QPointF(MIN2(sceneWidth, MAX2(0, endingPoint.x())), MIN2(sceneHeight, MAX2(0, endingPoint.y())));
        if (funnyTag)
            box->setPos(GETPOS(startPoint, endingPoint));
        else
            box->setPos(GETPOS(startPoint, endingPoint) + QPointF(0.01, 0.01));
        funnyTag = !funnyTag;
        box->setBounding(QRectF(QPointF(0, 0), GETSIZE(startPoint, endingPoint)));
    }
    else
        QGraphicsPixmapItem::mouseMoveEvent(event);
}

void backGround::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        endingPoint = event->pos();
        endingPoint = QPointF(MIN2(sceneWidth, MAX2(0, endingPoint.x())), MIN2(sceneHeight, MAX2(0, endingPoint.y())));
        emit newItem(QRectF(GETPOS(startPoint, endingPoint), GETSIZE(startPoint, endingPoint)));
        if (box)
        {
            delete box;
            box = NULL;
            startPoint = QPointF(0, 0);
            endingPoint = QPointF(0, 0);
        }
    }
}

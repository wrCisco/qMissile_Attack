#ifndef BASE_H
#define BASE_H

#include <QGraphicsPixmapItem>
#include <QPointF>

class Base : public QGraphicsPixmapItem
{
public:
    Base(QGraphicsItem *parent = nullptr);
    QPointF center();
};

#endif // BASE_H

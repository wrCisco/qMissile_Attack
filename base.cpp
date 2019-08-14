#include "base.h"


Base::Base(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/base"));
}

QPointF Base::center()
{
    return mapToScene(boundingRect().center());
}

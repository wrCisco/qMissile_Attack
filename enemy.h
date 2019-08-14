#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(int speed, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;

public slots:
    void move();

private:
    QRectF m_boundingRect;
    QPointF m_beginning;
    QPointF m_destination;
    int m_speed;
};

#endif // ENEMY_H

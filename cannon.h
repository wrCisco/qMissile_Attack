#ifndef CANNON_H
#define CANNON_H

#include <memory>

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPointF>

class Game;

class Cannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cannon(Game *game, QGraphicsItem *parent = nullptr);
    QPointF center();
    QPointF rotationPoint();
    QPointF firePoint();
    void setFirePoint();
    void fire(QPointF dest);
    void hit();
    bool isDamaged();

    QTimer *m_reparationTimer;

public slots:
    void repaired();

private:
    Game *game;
    QPointF m_rotationPoint;
    QPointF m_firePoint;
    bool m_damaged = false;
};

#endif // CANNON_H

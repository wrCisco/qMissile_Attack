#include <QPixmap>

#include "cannon.h"
#include "bullet.h"
#include "game.h"

#include <QDebug>

extern Game *game;

Cannon::Cannon(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/cannon"));

    m_rotationPoint = QPointF(boundingRect().width() / 2,
                              boundingRect().height() - 20);
    setTransformOriginPoint(m_rotationPoint);

    m_firePoint = QPointF(boundingRect().center().x(), 0);

    setZValue(1);

    m_reparationTimer = new QTimer(this);
    connect(m_reparationTimer, SIGNAL(timeout()), this, SLOT(repaired()));
}

QPointF Cannon::center()
{
    return mapToScene(boundingRect().center());
}

QPointF Cannon::rotationPoint()
{
    return m_rotationPoint;
}

QPointF Cannon::firePoint()
{
    return m_firePoint;
}

void Cannon::setFirePoint()
{
    m_firePoint = QPointF(boundingRect().center().x(), 0);
}

void Cannon::fire(QPointF dest)
{
    QLineF ln(mapToScene(rotationPoint()), dest);
    qreal angle = -1 * ln.angle();

    Bullet *bullet = new Bullet();

    bullet->setPos(mapToScene(firePoint()));
    bullet->setRotation(angle);
    game->m_scene->addItem(bullet);

    bullet->m_fireAudio.play();
}

void Cannon::hit()
{
    m_damaged = true;
    m_reparationTimer->start(2000);
}

void Cannon::repaired()
{
    m_damaged = false;
    m_reparationTimer->stop();
}

bool Cannon::isDamaged()
{
    return m_damaged;
}

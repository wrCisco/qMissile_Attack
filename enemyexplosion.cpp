#include <QTimer>
#include <QPainter>

#include "enemyexplosion.h"
#include "game.h"


EnemyExplosion::EnemyExplosion(Game *game, QGraphicsItem *parent) :
    QObject(),
    QGraphicsItem(parent),
    game { game },
    m_current_frame(0)
{
    connect(game->m_faster_animation_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}

void EnemyExplosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-40, -40, game->m_enemies_explosion_sheet,
                        m_current_frame, 0, 80, 80);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EnemyExplosion::nextFrame()
{
    m_current_frame += 80;
    if (m_current_frame >= 2560) {
        game->m_scene->removeItem(this);
        delete this;
        return;
    }
    update(boundingRect());
}

QRectF EnemyExplosion::boundingRect() const
{
    return QRectF(-40, -40, 80, 80);
}


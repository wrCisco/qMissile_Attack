#include <QTimer>
#include <QPainter>

#include "buildingexplosion.h"
#include "game.h"

extern Game *game;

BuildingExplosion::BuildingExplosion(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent), m_current_frame(0)
{
    connect(game->m_animation_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}

void BuildingExplosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, game->m_buildings_explosion_sheet,
                        m_current_frame, 0, 60, 146);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void BuildingExplosion::nextFrame()
{
    m_current_frame += 60;
    if (m_current_frame >= 2160) {
        game->m_scene->removeItem(this);
        delete this;
        return;
    }
    update(boundingRect());
}

QRectF BuildingExplosion::boundingRect() const
{
    return QRectF(0, 0, 60, 146);
}


/***
 *
 * Copyright (c) 2018, 2019 Francesco Martini
 *
 * This file is part of qMissile_Attack.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/


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


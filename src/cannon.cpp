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


#include <QPixmap>

#include "cannon.h"
#include "bullet.h"
#include "game.h"

#include <QDebug>


Cannon::Cannon(Game *game, QGraphicsItem *parent) :
    QObject(),
    QGraphicsPixmapItem(parent),
    game { game }
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

    Bullet *bullet = new Bullet(game);

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

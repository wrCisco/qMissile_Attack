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


#include <QRandomGenerator>
#include <QPixmap>
#include <QTimer>
#include <QList>
#include <qmath.h>

#include "enemy.h"
#include "game.h"
#include "building.h"
#include "base.h"
#include "buildingexplosion.h"


Enemy::Enemy(int speed, Game *game, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    game { game },
    m_speed(speed)
{
    setPixmap(game->m_enemies_pixmap);
    // set the center of the item to internal coordinates (0, 0)
    m_boundingRect = QRectF(-game->m_enemies_pixmap.width()/2,
                            -game->m_enemies_pixmap.height()/2,
                            game->m_enemies_pixmap.width(),
                            game->m_enemies_pixmap.height());

    // calculate start and ending point of missile's route
    m_beginning = QPointF(QRandomGenerator::global()->generate() % static_cast<unsigned int>(game->m_sceneWidth), 50);
    m_destination = QPointF(QRandomGenerator::global()->generate() % static_cast<unsigned int>(game->m_sceneWidth), 500);

    setPos(m_beginning);
    setOffset(-boundingRect().width()/2, -boundingRect().height()/2);
    QLineF ln(m_beginning, m_destination);
    qreal angle = -1 * ln.angle();
    setRotation(angle);

    connect(game->m_animation_timer, SIGNAL(timeout()), this, SLOT(move()));

}

QRectF Enemy::boundingRect() const
{
    return m_boundingRect;
}

void Enemy::move()
{
    double theta = rotation(); // degrees

    double dx = m_speed * qCos(qDegreesToRadians(theta));
    double dy = m_speed * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    if (y() - boundingRect().height() > game->m_sceneHeight) {
        game->m_scene->removeItem(this);
        delete this;
        return;
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Building *building = dynamic_cast<Building *>(colliding_items[i]);
        if (building && !building->m_hit) {
            BuildingExplosion *explosion = new BuildingExplosion(game);
            BuildingExplosion *explosion2 = new BuildingExplosion(game);
            QPointF explosion_point = building->mapToScene(building->boundingRect().center().x(),
                                                           building->boundingRect().height());
            game->m_scene->addItem(explosion);
            game->m_scene->addItem(explosion2);
            explosion->setPos(explosion_point.x(),
                              explosion_point.y()-explosion->boundingRect().height()-20);
            explosion2->setPos(explosion_point.x()-20,
                               explosion_point.y()-explosion->boundingRect().height()-30);
            building->destroyed();
            game->setBuildings(game->buildings()-1);
            game->m_scene->removeItem(this);
            delete this;
            return;
        }
        Base *base = dynamic_cast<Base *>(colliding_items[i]);
        if (base) {
            game->m_cannon->hit();
            game->m_scene->removeItem(this);
            delete this;
            return;
        }
    }

}


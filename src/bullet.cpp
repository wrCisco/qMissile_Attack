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
#include <QTimer>
#include <qmath.h>

#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "enemyexplosion.h"

#include <QDebug>


QUrl Bullet::m_audioSource("qrc:/audio/fire.wav");

Bullet::Bullet(Game *game, QGraphicsItem *parent) :
    QObject(),
    QGraphicsPixmapItem(parent),
    m_fireAudio(this),
    game { game }
{
    setPixmap(game->m_bullets_pixmap);

    m_boundingRect = QRectF(-game->m_bullets_pixmap.width()/2,
                            -game->m_bullets_pixmap.height()/2,
                            game->m_bullets_pixmap.width(),
                            game->m_bullets_pixmap.height());
    setOffset(-boundingRect().width()/2, -boundingRect().height()/2);

    connect(game->m_animation_timer, SIGNAL(timeout()), this, SLOT(move()));

    m_fireAudio.setSource(m_audioSource);
    m_fireAudio.setVolume(0.15);
}

QRectF Bullet::boundingRect() const
{
    return m_boundingRect;
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy) {
            QPointF explosion_point(enemy->mapToScene(enemy->boundingRect().center()));
            qreal explosion_rotation = enemy->rotation();
            EnemyExplosion *explosion = new EnemyExplosion(game);
            explosion->setPos(explosion_point);
            explosion->setRotation(explosion_rotation);
            game->m_scene->addItem(explosion);

            game->m_scene->removeItem(this);
            game->m_scene->removeItem(enemy);
            delete this;
            delete enemy;

            game->updateScore();
            return;
        }
    }

    // if the bullet goes outside the scene, remove it
    if (pos().x() + boundingRect().width() < 0 ||
            pos().x() - boundingRect().width() > game->m_sceneWidth ||
            pos().y() + boundingRect().height() < 0) {
        game->m_scene->removeItem(this);
        delete this;
    }
}

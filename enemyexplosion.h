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


#ifndef ENEMYEXPLOSION_H
#define ENEMYEXPLOSION_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QPointF>
#include <QTimer>

class Game;

class EnemyExplosion : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    EnemyExplosion(Game *game, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;

private slots:
    void nextFrame();

private:
    Game *game;
    QTimer *m_timer;
    QPixmap *m_explosion_sheet;
    int m_current_frame;
};

#endif // ENEMYEXPLOSION_H

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


#ifndef ENEMY_H
#define ENEMY_H

#include <memory>

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>

class Game;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(int speed, Game *game, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;

public slots:
    void move();

private:
    Game *game;
    QRectF m_boundingRect;
    QPointF m_beginning;
    QPointF m_destination;
    int m_speed;
};

#endif // ENEMY_H

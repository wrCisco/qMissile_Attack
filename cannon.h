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

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


#ifndef STATS_H
#define STATS_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Game;

class Stats : public QGraphicsRectItem
{
public:
    Stats(int w, int h, Game *game, QGraphicsItem *parent = nullptr);
    void updateLevelText();
    void updateScoreText();
    void updateBuildingsText();

private:
    Game *game;
    QGraphicsTextItem *m_level;
    QGraphicsTextItem *m_score;
    QGraphicsTextItem *m_buildings;
};

#endif // STATS_H

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


#include <QFontDatabase>
#include <QBrush>
#include <QColor>

#include "stats.h"
#include "game.h"


Stats::Stats(int width, int height, Game *game, QGraphicsItem *parent) :
    QGraphicsRectItem(parent),
    game { game }
{
    setPos(0, 0);
    setRect(0, 0, width, height);
    setBrush(QBrush(QColor(42, 42, 42, 255)));
    setPen(QPen(Qt::NoPen));
    setZValue(1);

    QColor statsTextColor = QColor(213, 213, 213);
    QFont statsFont = QFont(game->m_font_family);
    statsFont.setPixelSize(18);

    m_level = new QGraphicsTextItem(this);
    m_level->setPlainText(QString("Level: ") + QString::number(1));
    m_level->setDefaultTextColor(statsTextColor); // Qt::white);
    m_level->setFont(statsFont);
    m_level->setPos(width - m_level->boundingRect().width(), y());

    m_score = new QGraphicsTextItem(this);
    m_score->setPlainText(QString("Score: ") + QString::number(0));
    m_score->setDefaultTextColor(statsTextColor);
    m_score->setFont(statsFont);
    m_score->setPos(width - m_score->boundingRect().width(),
                  y() + m_level->boundingRect().height()*3/4);

    m_buildings = new QGraphicsTextItem(this);
    m_buildings->setPlainText(QString("Buildings left: ") + QString::number(4));
    m_buildings->setDefaultTextColor(statsTextColor);
    m_buildings->setFont(statsFont);
    m_buildings->setPos(x(), y() + m_level->boundingRect().height()*3/4);
}

void Stats::updateLevelText()
{
    m_level->setPlainText(QString("Level: ") + QString::number(game->level()));
    m_level->setPos(rect().width() - m_level->boundingRect().width(), y());
}

void Stats::updateScoreText()
{
    m_score->setPlainText(QString("Score: ") + QString::number(game->score()));
    m_score->setPos(rect().width() - m_score->boundingRect().width(),
                  y() + m_level->boundingRect().height()*3/4);
}

void Stats::updateBuildingsText()
{
    m_buildings->setPlainText(QString("Buildings left: ") + QString::number(game->buildings()));
}

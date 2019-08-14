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
#include <QSoundEffect>

#include "building.h"


QUrl Building::m_audioSource("qrc:/audio/building_explosion.wav");

Building::Building(QString pixmap, QGraphicsItem *parent) :
    QObject(),
    QGraphicsPixmapItem(parent),
    m_pixmap(pixmap),
    m_hit(false),
    m_explosionAudio(this)
{
    setPixmap(QPixmap(QString(":/images/") + m_pixmap));
    m_explosionAudio.setSource(m_audioSource);
}

void Building::destroyed()
{
    m_hit = true;
    setPixmap(QPixmap(QString(":/images/" + m_pixmap + "_destroyed")));
    m_explosionAudio.play();
}

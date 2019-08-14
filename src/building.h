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


#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include <QString>


class Building : public QObject, public QGraphicsPixmapItem
{
public:
    Building(QString pixmap, QGraphicsItem *parent = nullptr);
    void destroyed();
    QString m_pixmap;
    bool m_hit;

private:
    static QUrl m_audioSource;
    QSoundEffect m_explosionAudio;
};

#endif // BUILDING_H

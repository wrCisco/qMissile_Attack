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


#ifndef GAME_H
#define GAME_H

#include <memory>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCursor>
#include <QList>

#include "cannon.h"
#include "stats.h"
#include "building.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game();
    void populateScene();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void updateScore();
    void resetScore();
    int score();
    void levelUp();
    void resetLevel();
    int level();
    void setBuildings(int quantity);
    void resetBuildings();
    int buildings();
    void gameOver();

    QGraphicsScene *m_scene;
    const int m_sceneWidth = 800;
    const int m_sceneHeight = 500;

    Cannon *m_cannon;

    QTimer *m_animation_timer;
    QTimer *m_faster_animation_timer;
    QPixmap m_bullets_pixmap;
    QPixmap m_enemies_pixmap;
    QPixmap m_enemies_explosion_sheet;
    QPixmap m_buildings_explosion_sheet;

    QString m_font_family;

signals:

public slots:
    void spawnEnemies();

private:
    std::unique_ptr<QCursor> m_target_cursor;
    QTimer *m_spawn_enemies_timer;
    Stats *m_stats;
    QGraphicsRectItem *m_game_over_menu;
    QGraphicsTextItem *m_play_again;
    QMediaPlayer m_music;
    QMediaPlaylist m_playlist;
    int m_score = 0;
    int m_level = 1;
    int m_buildings = 4;
    int m_standing_buildings = 4;
    int m_enemy_speed = 4;
    int m_enemy_frequency = 1500; // 1 every 1500 milliseconds
    unsigned int m_max_enemy_spawned = 2;
    bool m_playing = true;
    bool m_play_again_is_bigger = false;
};

#endif // GAME_H

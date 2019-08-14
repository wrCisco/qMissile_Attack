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

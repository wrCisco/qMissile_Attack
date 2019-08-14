#include <QFontDatabase>
#include <QBrush>
#include <QColor>

#include "stats.h"
#include "game.h"

extern Game *game;

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

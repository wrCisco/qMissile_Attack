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

class EnemyExplosion : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    EnemyExplosion(QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;

private slots:
    void nextFrame();

private:
    QTimer *m_timer;
    QPixmap *m_explosion_sheet;
    int m_current_frame;
};

#endif // ENEMYEXPLOSION_H
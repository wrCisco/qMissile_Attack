#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include <QPixmap>
#include <QUrl>

#include "enemyexplosion.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    QSoundEffect m_fireAudio;

private slots:
    void move();

private:
    static QUrl m_audioSource;
    QRectF m_boundingRect;
};

#endif // BULLET_H

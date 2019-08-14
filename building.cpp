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

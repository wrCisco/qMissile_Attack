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

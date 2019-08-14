#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "enemyexplosion.h"

#include <QDebug>

extern Game *game;

QUrl Bullet::m_audioSource("qrc:/audio/fire.wav");

Bullet::Bullet(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), m_fireAudio(this)
{
    setPixmap(game->m_bullets_pixmap);

    m_boundingRect = QRectF(-game->m_bullets_pixmap.width()/2,
                            -game->m_bullets_pixmap.height()/2,
                            game->m_bullets_pixmap.width(),
                            game->m_bullets_pixmap.height());
    setOffset(-boundingRect().width()/2, -boundingRect().height()/2);

    connect(game->m_animation_timer, SIGNAL(timeout()), this, SLOT(move()));

    m_fireAudio.setSource(m_audioSource);
    m_fireAudio.setVolume(0.15);
}

QRectF Bullet::boundingRect() const
{
    return m_boundingRect;
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if (enemy) {
            QPointF explosion_point(enemy->mapToScene(enemy->boundingRect().center()));
            qreal explosion_rotation = enemy->rotation();
            EnemyExplosion *explosion = new EnemyExplosion();
            explosion->setPos(explosion_point);
            explosion->setRotation(explosion_rotation);
            game->m_scene->addItem(explosion);

            game->m_scene->removeItem(this);
            game->m_scene->removeItem(enemy);
            delete this;
            delete enemy;

            game->updateScore();
            return;
        }
    }

    // if the bullet goes outside the scene, remove it
    if (pos().x() + boundingRect().width() < 0 ||
            pos().x() - boundingRect().width() > game->m_sceneWidth ||
            pos().y() + boundingRect().height() < 0) {
        game->m_scene->removeItem(this);
        delete this;
    }
}

#include <QRandomGenerator>
#include <QPixmap>
#include <QTimer>
#include <QList>
#include <qmath.h>

#include "enemy.h"
#include "game.h"
#include "building.h"
#include "base.h"
#include "buildingexplosion.h"

extern Game *game;

Enemy::Enemy(int speed, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), m_speed(speed)
{
    setPixmap(game->m_enemies_pixmap);
    // set the center of the item to internal coordinates (0, 0)
    m_boundingRect = QRectF(-game->m_enemies_pixmap.width()/2,
                            -game->m_enemies_pixmap.height()/2,
                            game->m_enemies_pixmap.width(),
                            game->m_enemies_pixmap.height());

    // calculate start and ending point of missile's route
    m_beginning = QPointF(QRandomGenerator::global()->generate() % static_cast<unsigned int>(game->m_sceneWidth), 50);
    m_destination = QPointF(QRandomGenerator::global()->generate() % static_cast<unsigned int>(game->m_sceneWidth), 500);

    setPos(m_beginning);
    setOffset(-boundingRect().width()/2, -boundingRect().height()/2);
    QLineF ln(m_beginning, m_destination);
    qreal angle = -1 * ln.angle();
    setRotation(angle);

    connect(game->m_animation_timer, SIGNAL(timeout()), this, SLOT(move()));

}

QRectF Enemy::boundingRect() const
{
    return m_boundingRect;
}

void Enemy::move()
{
    double theta = rotation(); // degrees

    double dx = m_speed * qCos(qDegreesToRadians(theta));
    double dy = m_speed * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    if (y() - boundingRect().height() > game->m_sceneHeight) {
        game->m_scene->removeItem(this);
        delete this;
        return;
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Building *building = dynamic_cast<Building *>(colliding_items[i]);
        if (building && !building->m_hit) {
            BuildingExplosion *explosion = new BuildingExplosion();
            BuildingExplosion *explosion2 = new BuildingExplosion();
            QPointF explosion_point = building->mapToScene(building->boundingRect().center().x(),
                                                           building->boundingRect().height());
            game->m_scene->addItem(explosion);
            game->m_scene->addItem(explosion2);
            explosion->setPos(explosion_point.x(),
                              explosion_point.y()-explosion->boundingRect().height()-20);
            explosion2->setPos(explosion_point.x()-20,
                               explosion_point.y()-explosion->boundingRect().height()-30);
            building->destroyed();
            game->setBuildings(game->buildings()-1);
            game->m_scene->removeItem(this);
            delete this;
            return;
        }
        Base *base = dynamic_cast<Base *>(colliding_items[i]);
        if (base) {
            game->m_cannon->hit();
            game->m_scene->removeItem(this);
            delete this;
            return;
        }
    }

}


#include <memory>

#include <QGraphicsScene>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QRandomGenerator>
#include <QFontDatabase>
#include <QPixmap>
#include <QApplication>

#include "game.h"
#include "building.h"
#include "base.h"
#include "cannon.h"
#include "enemy.h"
#include "stats.h"


Game::Game() : QGraphicsView(),
    m_bullets_pixmap(":/images/bullet"),
    m_enemies_pixmap(":/images/enemy_missile"),
    m_enemies_explosion_sheet(":/images/missile_explosion"),
    m_buildings_explosion_sheet(":/images/building_explosion"),
    m_music(this)
{
    setAttribute(Qt::WA_DeleteOnClose);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0, 0, m_sceneWidth, m_sceneHeight);

    // the following two commented out rows can be used to add a border. See populateScene()
    //setFixedSize(sceneWidth+50, sceneHeight+25);
    //setSceneRect(0, 12.5, sceneWidth, sceneHeight);

    setFixedSize(m_sceneWidth, m_sceneHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png")));
    setScene(m_scene);

    // load embedded font
    int id = QFontDatabase::addApplicationFont(":/fonts/audiowide.ttf");
    m_font_family = QFontDatabase::applicationFontFamilies(id).at(0);

    // set cursor to be something more similar to a sight
    m_target_cursor = std::unique_ptr<QCursor>(new QCursor(Qt::CrossCursor));
    viewport()->setCursor(*m_target_cursor); // here would be sufficient viewport()->setCursor(Qt::CrossCursor);

    setMouseTracking(true);

    // create and connect timer to spawnEnemies
    m_spawn_enemies_timer = new QTimer(this);
    connect(m_spawn_enemies_timer, SIGNAL(timeout()), this, SLOT(spawnEnemies()));
    m_spawn_enemies_timer->start(m_enemy_frequency);

    // create timer for animations. Will be connected in varioues classes (Bullet, Enemy, BuildingExplosion)
    m_animation_timer = new QTimer(this);
    m_animation_timer->start(50);

    // for class EnemyExplosion
    m_faster_animation_timer = new QTimer(this);
    m_faster_animation_timer->start(25);

    // set background music
    m_playlist.addMedia(QUrl("qrc:/audio/bg.mp3"));
    m_playlist.setPlaybackMode(QMediaPlaylist::Loop);
    m_music.setPlaylist(&m_playlist);
    m_music.setVolume(30);
    m_music.play();

}

void Game::populateScene()
{
//    QGraphicsRectItem *border = new QGraphicsRectItem(-12.5, -12.5, sceneWidth+25, sceneHeight+25);
//    QPen borderPen(QColor(42, 42, 42), 25);
//    borderPen.setJoinStyle(Qt::MiterJoin);
//    border->setPen(borderPen);
//    border->setZValue(2);
//    scene->addItem(border);

    m_stats = new Stats(m_sceneWidth, 55);
    m_scene->addItem(m_stats);

    const qreal dist_buildings = 65.0;
    Building *building1 = new Building("yellow_home");
    m_scene->addItem(building1);
    qreal offsetX = dist_buildings;
    building1->setPos(offsetX, m_sceneHeight - building1->boundingRect().height() + 3);

    Building *building2 = new Building("gas_station");
    m_scene->addItem(building2);
    offsetX += building1->boundingRect().width() + dist_buildings;
    building2->setPos(offsetX, m_sceneHeight - building2->boundingRect().height() + 3);

    Base *base = new Base();
    m_scene->addItem(base);
    base->setPos(m_sceneWidth / 2 - base->boundingRect().width() / 2,
                 m_sceneHeight - base->boundingRect().height() / 2);

    Building *building3 = new Building("white_home");
    m_scene->addItem(building3);
    offsetX = base->center().x() + base->boundingRect().width() / 2 + dist_buildings;
    building3->setPos(offsetX, m_sceneHeight - building3->boundingRect().height() + 3);

    Building *building4 = new Building("green_palace");
    m_scene->addItem(building4);
    offsetX += building3->boundingRect().width() + dist_buildings;
    building4->setPos(offsetX, m_sceneHeight - building4->boundingRect().height() + 3);

    m_cannon = new Cannon();
    m_scene->addItem(m_cannon);
    m_cannon->setPos(m_sceneWidth / 2 - m_cannon->boundingRect().width() / 2,
                     m_sceneHeight - m_cannon->rotationPoint().y());

}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (isActiveWindow()) {
        QLineF ln(event->pos(), m_cannon->mapToScene(m_cannon->rotationPoint()));

        qreal angle = -1 * ln.angle() - 90;
        while (angle < 0) angle += 360;
        m_cannon->setRotation(angle);
        m_cannon->setFirePoint();

        if (!m_playing) {
            if (m_play_again->contains(m_play_again->mapFromScene(event->pos())) && !m_play_again_is_bigger) {
                m_play_again_is_bigger = true;
                m_play_again->setScale(1.2);
            }
            else if (!m_play_again->contains(m_play_again->mapFromScene(event->pos())) && m_play_again_is_bigger) {
                m_play_again_is_bigger = false;
                m_play_again->setScale(1.0);
            }
        }
    }
    else {
        QWidget::mouseMoveEvent(event);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (m_playing && !m_cannon->isDamaged()) {
        m_cannon->fire(QPointF(event->pos()));
    }
    else if (!m_playing && m_game_over_menu){
        if (m_play_again->contains(m_play_again->mapFromScene(event->pos()))) {
            m_scene->clear();
            populateScene();
            resetScore();
            resetLevel();
            resetBuildings();
            m_playing = true;
        }
    }
}

void Game::focusOutEvent(QFocusEvent *event)
{
    // when the game loses focus, pause it
    m_spawn_enemies_timer->stop();
    m_animation_timer->stop();
    m_faster_animation_timer->stop();
    if (m_cannon->isDamaged()) {
        m_cannon->m_reparationTimer->stop();
    }
    m_music.pause();

    QWidget::focusOutEvent(event);
}

void Game::focusInEvent(QFocusEvent *event)
{
    // On mouse click the game will unpause and the cannon will shoot,
    // but cannon won't rotate until a mouse move event is sent to the view.
    QMouseEvent e(QEvent::MouseMove,
                  mapFromGlobal(QCursor::pos()),
                  Qt::NoButton,
                  Qt::NoButton,
                  Qt::NoModifier);
    QApplication::sendEvent(viewport(), &e);

    m_spawn_enemies_timer->start();
    m_animation_timer->start();
    m_faster_animation_timer->start();
    if (m_cannon->isDamaged()) {
        m_cannon->m_reparationTimer->start();
    }
    m_music.play();

    QWidget::focusInEvent(event);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape ||
        (event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier))
        close();
}

void Game::updateScore()
{
    ++m_score;
    m_stats->updateScoreText();
    if (m_score == 10 * m_level + m_level * m_level) levelUp();
}

void Game::resetScore()
{
    m_score = 0;
}

int Game::score()
{
    return m_score;
}

int Game::level()
{
    return m_level;
}

int Game::buildings()
{
    return m_standing_buildings;
}

void Game::setBuildings(int quantity)
{
    m_standing_buildings = quantity;
    m_stats->updateBuildingsText();
    if (!m_standing_buildings) gameOver();
}

void Game::resetBuildings()
{
    setBuildings(m_buildings);
}

void Game::levelUp()
{
    ++m_level;
    m_stats->updateLevelText();
    m_enemy_speed += 2;
    m_enemy_frequency -= 100;
    m_spawn_enemies_timer->setInterval(m_enemy_frequency);
    if (m_level % 3 == 0) {
        m_max_enemy_spawned += 1;
    }
}

void Game::resetLevel()
{
    m_level = 1;
    m_stats->updateLevelText();
    m_enemy_speed = 4;
    m_enemy_frequency = 1500;
    m_spawn_enemies_timer->start(m_enemy_frequency);
    m_max_enemy_spawned = 2;
}

void Game::gameOver()
{
    m_game_over_menu = new QGraphicsRectItem(0, 0, m_scene->width(), m_scene->height());
    QGraphicsTextItem *game_over = new QGraphicsTextItem(QString("Game over"), m_game_over_menu);
    game_over->setDefaultTextColor(Qt::red);
    game_over->setFont(QFont(m_font_family, 48));
    game_over->setPos(m_scene->width()/2 - game_over->boundingRect().width()/2,
                      m_scene->height()/3 - game_over->boundingRect().height()/2);
    m_play_again = new QGraphicsTextItem(QString("Play again"), m_game_over_menu);
    m_play_again->setDefaultTextColor(Qt::red);
    m_play_again->setFont(QFont(m_font_family, 24));
    m_play_again->setPos(m_scene->width()/2 - m_play_again->boundingRect().width()/2,
                       m_scene->height()/3 + game_over->boundingRect().height()/2);
    m_play_again->setTransformOriginPoint(m_play_again->boundingRect().center());
    m_scene->addItem(m_game_over_menu);

    m_spawn_enemies_timer->stop();

    m_playing = false;
}

void Game::spawnEnemies()
{
    unsigned int enemies = QRandomGenerator::global()->generate() % (m_max_enemy_spawned + 1);
    for (unsigned int i = 0; i < enemies; ++i) {
        Enemy *enemy = new Enemy(m_enemy_speed);
        m_scene->addItem(enemy);
    }
}

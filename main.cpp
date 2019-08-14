#include <memory>

#include <QApplication>
#include <QIcon>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/enemy_missile"));

    Game *game = new Game();
    game->populateScene();
    game->show();

    return a.exec();
}

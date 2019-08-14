#include "game.h"
#include <QApplication>
#include <QIcon>

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/enemy_missile"));

    game = new Game();
    game->populateScene();
    game->show();

    return a.exec();
}

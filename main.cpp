#include "mainwindow.h"
#include "map.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

    Game* game = new Game();
    game->startGame();

    return 0;
}

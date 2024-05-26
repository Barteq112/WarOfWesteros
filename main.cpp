#include "mainwindow.h"
#include "game.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

    Game* game = new Game();
    game->startGame();
    // testowe dodanie jedneostek do armii północy i wyświetlenie ich
    // testowe dodanie jednostek do armii północy i wyświetlenie ich
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Infantry>(1));
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Cavalry>(2));




}

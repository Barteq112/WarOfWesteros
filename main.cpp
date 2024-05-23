#include "mainwindow.h"
#include "map.h"
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
    //testowe dodanie budynku do królestwa północy
    game->getKingdomNorth()->buildBuilding( 0, 0, game);
    //print mapy budynków w konsoli
    // for(int i=0; i<game->getMap()->getMapWidth(); i++) {
    //     for(int j=0; j<game->getMap()->getMapHeight(); j++) {
    //         if(game->getMap()->getTile(i,j)->getBuilding() != nullptr) {
    //             std::cout << "B";
    //         } else {
    //             std::cout << "0";
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    // return 0;

    std::cout<<game->getMap()->getTile(0,0)->getBuilding();

}

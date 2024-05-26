#include "game.h"

Game::Game() {
    //inicjalizacja królestw
    KingdomNorth = new Kingdom();
    KingdomSouth = new Kingdom();
    KingdomBeyondTheWall = new Kingdom();
    //inicjalizacja mapy
    map = new Map(1000,1000);
    KingdomSouth->setOwner(0);
    KingdomNorth->setOwner(1);
    KingdomBeyondTheWall->setOwner(2);
    KingdomSouth->setMap(this->map);
    KingdomNorth->setMap(this->map);
    KingdomBeyondTheWall->setMap(this->map);
}

void Game::endGame() {
    delete KingdomNorth;
    delete KingdomSouth;
    delete KingdomBeyondTheWall;
    delete map;
}

void Game::startGame() {
    //Podział mapy
    for(int i=0; i<map->getMapWidth(); i++) {
        for(int j=0; j<map->getMapHeight(); j++) {
            if(i<map->getMapWidth()/3) {
                map->getTile(i,j)->setOwner(KingdomNorth);
            } else if(i<2*map->getMapWidth()/3) {
                map->getTile(i,j)->setOwner(KingdomSouth);
            } else {
                map->getTile(i,j)->setOwner(KingdomBeyondTheWall);
            }
        }
    }

}



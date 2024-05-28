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


// 0 - South, 1 - North, 2 - BeyondTheWall
void Game::startGame() {
    //Podział mapy
    for(int i=0; i<map->getMapWidth(); i++) {
        for(int j=0; j<map->getMapHeight(); j++) {
            if(i<map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(0);
            } else if(i<2*map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(1);
            } else {
                map->getTile(i,j)->setOwner(2);
            }
        }
    }

}



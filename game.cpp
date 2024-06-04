#include "game.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <chrono>

Game::Game() {
    //inicjalizacja królestw
    KingdomNorth = new Kingdom();
    KingdomSouth = new Kingdom();
    KingdomBeyondTheWall = new Kingdom();
    //inicjalizacja mapy
    map = new Map(150,80);
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
}

bool Game::isGameEnded()
{
    int c=0;
    if(KingdomBeyondTheWall == nullptr)
        c++;
    if(KingdomNorth == nullptr)
        c++;
    if(KingdomSouth == nullptr)
        c++;
    if(c>=2)
        return true;
    return false;
}


// 0 - South, 1 - North, 2 - BeyondTheWall
void Game::startGame() {
    //Podział mapy
    for(int i=0; i<map->getMapWidth(); i++) {
        for(int j=0; j<map->getMapHeight(); j++) {
            if(j<map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(0);
            } else if(j<2*map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(1);
            } else {
                map->getTile(i,j)->setOwner(2);
            }
        }
    }

    //Postawienie zamku głównego dla każdego królestwa
    KingdomSouth->buildMainCastle(1,1);
    KingdomNorth->buildMainCastle(map->getMapWidth()-4,map->getMapHeight()/2);
    KingdomBeyondTheWall->buildMainCastle(1,map->getMapHeight()-5);



}


void Game::autoMoveAttack()
{

    std::vector<std::shared_ptr<Unit>> allUnits;

    // Sprawdzenie, czy królestwa mają jednostki, zanim je dodamy do allUnits
    if(this->KingdomSouth != nullptr)
    {
        auto southUnits = getKingdomSouth()->getArmy().getUnits();
        if (!southUnits.empty()) {
            allUnits.insert(allUnits.end(), southUnits.begin(), southUnits.end());
        }
    }

    if(this->KingdomBeyondTheWall != nullptr)
    {
        auto beyondTheWallUnits = getKingdomBeyondTheWall()->getArmy().getUnits();
        if (!beyondTheWallUnits.empty()) {
            allUnits.insert(allUnits.end(), beyondTheWallUnits.begin(), beyondTheWallUnits.end());
        }
    }
    if(this->KingdomNorth != nullptr)
    {
        auto northUnits = getKingdomNorth()->getArmy().getUnits();
        if (!northUnits.empty()) {
            allUnits.insert(allUnits.end(), northUnits.begin(), northUnits.end());
        }
    }

    // Pobierz czas początkowy
    auto currentTime = std::chrono::system_clock::now();

    // Przemieszaj jednostki
    if(allUnits.size() > 1)
        std::random_shuffle(allUnits.begin(), allUnits.end());
    // Przejdź po liście i wykonaj ruch każdej jednostki
    for (auto unit : allUnits)
    {

        if (unit->inMotion() && std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - unit->getLastMoveTime()).count() >3000/unit->getSpeed())
        {
            unit->move(this->getMap());
            unit->setLastMoveTime();
        }

        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - unit->getLastAttackTime()).count() >2000/unit->getAttackSpeed())
        {
            unit->attack(this);
            unit->setLastAttackTime();
        }

    }
}



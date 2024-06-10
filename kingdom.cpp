#include "kingdom.h"
#include "map.h"
#include "building.h"
#include <iostream>

Kingdom::Kingdom() : resources(10000,10) {
    this->getArmy().setOwner(this->owner);
    this->getArmy().setMap(this->map);
}

void Kingdom::buildMainCastle(int x, int y)
{
    if(map->placeIsAvailable(x,y,mainCastleSizeX,mainCastleSizeY)==false || map->isYourPlace(x,y,mainCastleSizeX,mainCastleSizeY,owner)==false)
    {
        return;
    }
    std::shared_ptr<MainCastle> mainCastle = std::make_shared<MainCastle>();
    buildings.push_back(mainCastle);
    map->setBuildingOnMap(x,y,mainCastle);
    mainCastle->setX(x);
    mainCastle->setY(y);
    mainCastle->setOwner(this->owner);

}

void Kingdom::buildBarracks(int x, int y)
{
    if(map->placeIsAvailable(x,y,barracksSizeX,barracksSizeY)==false || map->isYourPlace(x,y,mainCastleSizeX,mainCastleSizeY,owner)==false)
    {

        return;
    }
    std::shared_ptr<Barracks> barracks = std::make_shared<Barracks>();
    buildings.push_back(barracks);
    map->setBuildingOnMap(x,y,barracks);
    barracks->setX(x);
    barracks->setY(y);
    barracks->setOwner(this->owner);
}

void Kingdom::buildHouse(int x, int y)
{
    if(map->placeIsAvailable(x,y,houseSizeX,houseSizeY)==false || map->isYourPlace(x,y,mainCastleSizeX,mainCastleSizeY,owner)==false)
    {
        return;
    }
    std::shared_ptr<House> house = std::make_shared<House>();
    buildings.push_back(house);
    map->setBuildingOnMap(x,y,house);
    house->setX(x);
    house->setY(y);
    house->setOwner(this->owner);
    //Dodaj populacje
    resources.increasePopulation(house->getHousePopulation());

}

void Kingdom::removeBuildingFromList(int x, int y)
{
    auto building = map->getTile(x, y)->getBuilding();
    if (building == nullptr)
    {
        return;
    }

    for (auto it = buildings.begin(); it != buildings.end(); ++it)
    {
        if (*it == building)
        {
            buildings.erase(it);
            break;
        }
    }
}

int Kingdom::checkHouses()
{
    //Sprawdza liczbę domów
    int houses = 0;
    for(auto building : buildings)
    {
        if(building->getType() == 2)
        {
            houses++;
        }
    }
    return houses;
}

int Kingdom::checkCastleLevel()
{
    //Sprawdza level zamku
    for(auto building : buildings)
    {
        if(building->getType() == 0)
        {
            auto castle = std::dynamic_pointer_cast<MainCastle>(building);
            return castle->getLevel();
        }
    }
    return 0;
}



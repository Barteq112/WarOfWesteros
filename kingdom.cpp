#include "kingdom.h"
#include "map.h"
#include "building.h"
#include <iostream>
#include <chrono>
#include "game.h"

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

void Kingdom::autoRun(Game *game)
{
    // Uruchamia zegar
    auto last = std::chrono::high_resolution_clock::now();
    //stawia barki w losowym miejscu w odległości 8 od zamku
    auto[x,y]= map->findClosestFreeTile(getBuildings().at(0)->getX(), getBuildings().at(0)->getY(),mainCastleSizeX,mainCastleSizeY);
        buildBarracks(x,y);
    auto mainCastle = std::dynamic_pointer_cast<MainCastle>(getBuildings().at(0));
    auto barracks = std::dynamic_pointer_cast<Barracks>(getBuildings().at(1));
    //stawia dom w losowym miejscu w odległości 8 od zamku
    int x1 = mainCastle->getX();
    int y1 = mainCastle->getY();
    x1 = x1 + (rand() % 16 - 8);
    y1 = y1 + (rand() % 16 - 8);
    auto[x11,y11] = map->checkCoordinates(x1,y1);
    std::cout<<"x1: "<<x11<<" y1: "<<y11<<std::endl;
    auto[x2,y2]= map->findClosestFreeTile(x11, y11,houseSizeX,houseSizeY,owner);
    std::cout<<"x2: "<<x2<<" y2: "<<y2<<std::endl;
    buildHouse(x2,y2);
    while(0)
    {
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()-last).count() >= 20)
        {
            //jeżli brak populacji stawia dom
            if(resources.getPopulation() == 0)
            {
                auto[x,y]= map->findClosestFreeTile(mainCastle->getX(), mainCastle->getY(),houseSizeX,houseSizeY,owner);
                buildHouse(x,y);
            }
            //co 20 sekund dodaje jednostki do armii
            barracks->RecruitUnit(1, game);
            last = std::chrono::high_resolution_clock::now();
        }
        {

        }
    }



}



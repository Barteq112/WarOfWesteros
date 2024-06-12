#include "kingdom.h"
#include "map.h"
#include "building.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "game.h"

Kingdom::Kingdom() : resources(1000,10) {
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
    if(map->placeIsAvailable(x,y,barracksSizeX,barracksSizeY)==false || map->isYourPlace(x,y,barracksSizeX,barracksSizeY,owner)==false)
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
    if(map->placeIsAvailable(x,y,houseSizeX,houseSizeY)==false || map->isYourPlace(x,y,houseSizeX,houseSizeY,owner)==false)
    {
        std::cout<<"dupa";
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


void Kingdom::grantGold()
{
    //std::cout << "Granting gold to kingdom " << name << std::endl;
    auto mainCastle = std::dynamic_pointer_cast<MainCastle>(getBuildings().at(0));
    int castleLevel = mainCastle->getLevel();    // Zakładając, że MainCastle ma funkcję getLevel()
    int numBuildings = getBuildings().size();
    int goldToAdd = std::min(300, castleLevel * 100 + numBuildings * 100);

    resources.increaseGold(goldToAdd); // Zakładając, że Resources ma funkcję addGold()
}


void Kingdom::autoRun(Game *game)
{
    // Uruchamia zegar
    auto start = std::chrono::high_resolution_clock::now();
    auto lastRecruitTime = start;
    auto lastAttackTime = start;

    // Stawia baraki w losowym miejscu w odległości 8 od zamku po 10 sekundach
    std::thread([this, game, lastRecruitTime, lastAttackTime]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000 + 1000));
        auto [x, y] = map->findClosestFreeTile(getBuildings().at(0)->getX(), getBuildings().at(0)->getY(), mainCastleSizeX, mainCastleSizeY);

        buildBarracks(x, y);

        auto mainCastle = std::dynamic_pointer_cast<MainCastle>(getBuildings().at(0));
        auto barracks = std::dynamic_pointer_cast<Barracks>(map->getTile(x, y)->getBuilding());

        std::srand(static_cast<unsigned>(std::time(nullptr)) + std::hash<std::thread::id>{}(std::this_thread::get_id()));
        while (true)
        {
            auto now = std::chrono::high_resolution_clock::now();

            // Losowe czasy dla rekrutacji i ataku
            int recruitTime = 2 + std::rand() % 2;  // Losuje liczbę z zakresu 2-3
            int attackTime = 9 + std::rand() % 4;   // Losuje liczbę z zakresu 9-12


            //std::cout<<owner<<"  "<<getResources().getGold()<<" d"<<std::endl;
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastRecruitTime).count() >= recruitTime && getResources().getGold() > 200)
            {

                if (resources.getPopulation() <= 0)
                {
                    auto [hx, hy] = map->findClosestFreeTile(mainCastle->getX(), mainCastle->getY(), houseSizeX, houseSizeY, owner);

                    buildHouse(hx, hy);
                }
                else
                {
                    if(barracks==nullptr)
                    {
                        std::cout<<"Barracks not found";
                        return;
                    }
                    auto availableUnits = southUnitPrices;
                    int random = std::rand() % 5;

                    int unitType = availableUnits.at(random).type; // Zakładając, że UnitPrice ma pole 'type'

                    barracks->RecruitUnit(unitType, game);
                }
                lastRecruitTime = now;
            }

            // Sprawdza czy czas na atak
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastAttackTime).count() >= attackTime)
            {
                Kingdom* targetKingdom = nullptr;
                std::vector<Kingdom*> kingdoms = {game->getKingdomSouth(), game->getKingdomNorth(), game->getKingdomBeyondTheWall()};

                // Wybiera losowe królestwo, upewniając się, że nie jest to nullptr ani własne królestwo
                while (true)
                {
                    targetKingdom = kingdoms[std::rand() % kingdoms.size()];
                    if (targetKingdom != nullptr && targetKingdom != this)
                    {
                        break;
                    }
                }

                if (targetKingdom)
                {
                    auto targetCastle = targetKingdom->getBuildings().at(0);
                    int targetX = targetCastle->getX();
                    int targetY = targetCastle->getY();

                    for (auto& unit : getArmy().getUnits())
                    {
                        unit->setDestination(targetX, targetY);
                    }
                }
                lastAttackTime = now;
            }

            // Krótki czas oczekiwania przed następną iteracją
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }).detach();
}



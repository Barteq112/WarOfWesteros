#ifndef KINGDOM_H
#define KINGDOM_H
#include <string>
#include <vector>
#include <memory>
#include "resources.h"
#include "army.h"
#include "building.h"
#include "map.h"


class Kingdom
{
private:
    int owner;
    std::string name;
    Resources resources;
    Army army;
    std::vector<std::shared_ptr<Building>> buildings;
    Map* map;

public:
    Kingdom();
    Resources& getResources() {return resources;}
    Army& getArmy() {return army;}
    std::vector<std::shared_ptr<Building>> getBuildings() {return buildings;}
    void setName(std::string name) {this->name = name;}
    std::string getName() {return name;}
    void buildMainCastle(int x, int y);
    void buildBarracks(int x, int y);
    void buildHouse(int x, int y);
    void removeBuildingFromList(int x, int y);
    //Sprawdza liczbę domów
    int checkHouses();
    //Sprawdza level zamku
    int checkCastleLevel();
    void setOwner(int owner) {this->owner = owner;}
    void setMap(Map* map) {this->map = map;}
    void grantGold();
    void autoRun(Game *game);
};

#endif // KINGDOM_H

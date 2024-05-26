#ifndef KINGDOM_H
#define KINGDOM_H
#include <string>
#include <vector>
#include <memory>
#include "resources.h"
#include "army.h"
#include "building.h"


class Game;


class Kingdom
{
private:
    std::string name;
    Resources resources;
    Army army;
    std::vector<std::shared_ptr<Building>> buildings;

public:
    Kingdom();
    Resources& getResources() {return resources;}
    Army& getArmy() {return army;}
    std::vector<std::shared_ptr<Building>> getBuildings() {return buildings;}
    void setName(std::string name) {this->name = name;}
    std::string getName() {return name;}
    void buildMainCastle(int x, int y, Game *gra);
    void buildBarracks(int x, int y, Game *gra);
    void buildHouse(int x, int y, Game *gra);
};

#endif // KINGDOM_H

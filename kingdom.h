#ifndef KINGDOM_H
#define KINGDOM_H
#include <string>
#include <vector>
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
    std::vector<Building> buildings;

public:
    Kingdom();
    Resources& getResources() {return resources;}
    Army& getArmy() {return army;}
    std::vector<Building>& getBuildings() {return buildings;}
    void setName(std::string name) {this->name = name;}
    std::string getName() {return name;}
    void buildBuilding(int x, int y, Game *gra, int type);
};

#endif // KINGDOM_H

#ifndef KINGDOM_H
#define KINGDOM_H
#include <string>
#include <vector>
#include "resources.h"
#include "army.h"
#include "building.h"

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

};

#endif // KINGDOM_H

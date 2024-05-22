#ifndef KINGDOM_H
#define KINGDOM_H
#import <string>
#import <vector>
#import "resources.h"
#import "army.h"
#import "building.h"

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

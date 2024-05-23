#include "kingdom.h"
#include "game.h"

Kingdom::Kingdom() {}

void buildBuilding(int x, int y, Game *gra, int type) {
    Building building;
    //dodanie budynku do listy budynków królestwa
    buildings.push_back(building);
    //dodanie budynku na mapie o danym rozmiarze
    for(int i=x; i<x+building.getSizex(); i++) {
        for(int j=y; j<y+building.getSizey(); j++) {
            gra->getMap()->getTile(i,j)->setBuilding(&building);
        }
    }

}

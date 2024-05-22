#ifndef MAP_H
#define MAP_H

#include <vector>
#include "kingdom.h"
#include "building.h"
#include "army.h"

class Map_tile
{
private:
    Kingdom* owner;
    Building* building;
    Unit* unit;
    bool isAvailable;


public:
    Map_tile();

    //zwraca czy kafelek jest dostępny
    bool getIsAvailable();
    //ustawia czy kafelek jest dostępny
    void setIsAvailable(bool available);
    //zwraca właściciela kafelka
    Kingdom* getOwner();
    //ustawia właściciela kafelka
    void setOwner(Kingdom* owner);
    //zwraca budynek na kafelku
    Building* getBuilding();
    //ustawia budynek na kafelku
    void setBuilding(Building* building);
    //usuwa budynek z kafelka
    void removeBuilding();
    //zwraca jednostkę na kafelku
    Unit* getUnit();
    //ustawia jednostkę na kafelku
    void setUnit(Unit* unit);
    //usuwa jednostkę z kafelka
    void removeUnit();

};

class Map
{
private:
    //mapa stowrzona z wektorów wektorów kafelków
    std::vector<std::vector<Map_tile>> map;
    //rozmiar mapy
    int size_x, size_y;
public:
    //tworzy mape o podanym rozmiarze
    Map(int size_x, int size_y);
    //zwraca szerokość mapy
    int getMapWidth();
    //zwraca wysokość mapy
    int getMapHeight();
    //zwraca kafelek o podanych współrzędnych
    Map_tile* getTile(int x, int y);


};



#endif // MAP_H

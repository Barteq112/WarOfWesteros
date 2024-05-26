#ifndef MAP_H
#define MAP_H

#include <vector>
#include<memory>
#include "kingdom.h"
#include "building.h"
#include "army.h"

class Game;

class Map_tile
{
private:
    Kingdom* owner;
    std::shared_ptr<Building> building;
    std::shared_ptr<Unit> unit;
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
    std::shared_ptr<Building> getBuilding();
    //ustawia budynek na kafelku
    void setBuilding(std::shared_ptr<Building> building);
    //usuwa budynek z kafelka
    void removeBuilding();
    //zwraca jednostkę na kafelku
    std::shared_ptr<Unit> getUnit();
    //ustawia jednostkę na kafelku
    void setUnit(std::shared_ptr<Unit> unit);
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
    //sprawdza czy kafelki pod budynek lub jednostkę są dostępne
    bool placeIsAvailable(int x, int y, int sizex , int sizey);
    //Zwraca najbliższą wrogą jednostkę w zasięgu od podanych współrzędnych
    std::shared_ptr<Unit> getClosestEnemy(int x, int y, int range, int owner);
    //Zwraca vector wrogich jednostek w zasięgu od podanych współrzędnych
    std::vector<std::shared_ptr<Unit>> getEnemiesInRange(int x, int y, int range, int owner);
    //Zwraca listę sojuszniczych jednostek w zasięgu od podanych współrzędnych
    std::vector<std::shared_ptr<Unit>> getUnitsInRange(int x, int y, int range, int owner);
    //Zwraca najbliższy wrogi budynek w zasięgu od podanych współrzędnych
    std::shared_ptr<Building> getClosestEnemyBuilding(int x, int y, int range, int owner);
    //Ustawia budynek na mapie w podanym miejscu o podanym rozmiarze i ustawia kafelki niedostępne
    void setBuildingOnMap(int x, int y, std::shared_ptr<Building> building);
    //Usuwa budynek z mapy i ustawia kafelki jako dostępne
    void removeBuildingFromMap(int x, int y, std::shared_ptr<Building> building);
    //Ustawa jednostkę na mapie w podanym miejscu i ustawia kafelki niedostępne
    void setUnitOnMap(int x, int y, std::shared_ptr<Unit> unit);
    //Usuwa jednostkę z mapy i ustawia kafelki jako dostępne
    void removeUnitFromMap(int x, int y);





};



#endif // MAP_H

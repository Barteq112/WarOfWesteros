#ifndef MAP_H
#define MAP_H

#include <vector>
#include<memory>
#include "building.h"
#include "army.h"

class Game;

class Map_tile
{
private:
    int owner;
    std::shared_ptr<Building> building;
    std::shared_ptr<Unit> unit;
    bool isAvailable = true;


public:
    Map_tile();

    //zwraca czy kafelek jest dostępny
    bool getIsAvailable();
    //ustawia czy kafelek jest dostępny
    void setIsAvailable(bool available);
    //zwraca właściciela kafelka
    int getOwner();
    //ustawia właściciela kafelka
    void setOwner(int owner);
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
    Map(int size_x, int size_y)
    {
        this->size_x = size_x;
        this->size_y = size_y;
        map.resize(size_x);
        for(int i = 0; i < size_x; i++)
        {
            map[i].resize(size_y);
        }
        this->size_x = size_x-1;
    }
    //zwraca szerokość mapy
    int getMapWidth();
    //zwraca wysokość mapy
    int getMapHeight();
    //zwraca kafelek o podanych współrzędnych
    Map_tile* getTile(int x, int y);
    //sprawdza czy kafelki pod budynek lub jednostkę są dostępne
    bool placeIsAvailable(int x, int y, int sizex , int sizey);
    //Sprawdza czy kafelki są dostępne dla jesnodtki, ale jeżeli on na tym kafelku toi to też zwraca jako dostępne
    bool placeIsAvailableForUnit(int x, int y, int sizex, int sizey, std::shared_ptr<Unit> unit);
    //sprawdza czy kafelki pod budynek są twoje
    bool isYourPlace(int x, int y, int sizex, int sizey, int owner);
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
    //Znajduję najbliższe wolne miejsce od podanych współrzędnych i podanego rozmiaru
    std::pair<int,int> findClosestFreeTile(int x, int y, int sizex, int sizey);
    //Znajduję najbliższe wolne miejsce od podanych współrzędnych i podanego rozmiaru oraz należące do podanego właściciela
    std::pair<int, int> findClosestFreeTile(int x, int y, int sizex, int sizey, int owner);
    //Zwraca mape dostępnych kafelków
    std::vector<std::vector<bool>> getAvailableTiles();
    //sprawdza czy czy współrzędne są w obrębie mapy jeżeli nie to zwraca najbliższe wzpółrzędne w obębie mapy
    std::pair<int,int> checkCoordinates(int x, int y);





};



#endif // MAP_H

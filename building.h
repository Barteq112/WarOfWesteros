#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

//Stałe wymiary budynków
constexpr int mainCastleSizeX = 27;
constexpr int mainCastleSizeY = 45;
constexpr int barracksSizeX = 25;
constexpr int barracksSizeY = 25;
constexpr int houseSizeX = 20;
constexpr int houseSizeY = 20;




struct UnitPrice
{
    std::string name;
    int price;
};



//Typ budynku, 0- MainCastle, 1 - Barracks, 2 - House
class Building
{
protected:
    int x;
    int y;
    int cost;
    int sizex;
    int sizey;
    int health;
    int owner;  // 0 - South, 1 - North, 2 - BeyondTheWall
    int type;
public:
    Building();
    void removeBuilding();
    void decreaseHealth(int amount);
    void increaseHealth(int amount);
    int getSizex(){return sizex;};
    int getSizey(){return sizey;};
    int getOwner(){return owner;};
    int getCost(){return cost;};
    int getHealth(){return health;};
};

class MainCastle : public Building
{
private:
    int level;
public:
    void upgradeCastle();
    MainCastle() : level(0) {this->type = 0;  this->sizex = mainCastleSizeX; this->sizey = mainCastleSizeY; this->health = 1000;};
};

class Barracks : public Building
{
private:

    std::vector<UnitPrice> availableUnits;

public:
    Barracks(){this->type = 1; this->sizex = barracksSizeX; this->sizey = barracksSizeY; this->health = 800;} ;
    std::vector<UnitPrice> getAvailableUnits(){return availableUnits;};
    void RecruitUnit(std::string name);

};

class House : public Building
{
    private:
        int HousePopulation;
    public:
        House(){this->type = 2; this->sizex = houseSizeX; this->sizey = houseSizeY; this->health = 500; this->HousePopulation = 10;};
        //Usuwa populacje z królestwa po zniszczeniu domu
        void DeletePopulation(int amount);

};


#endif // BUILDING_H

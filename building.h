#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

struct UnitPrice
{
    std::string name;
    int price;
};

std::vector<UnitPrice> unitPricesNorth = {

};

std::vector<UnitPrice> unitPricesSouth = {

};

std::vector<UnitPrice> unitPricesBeyondTheWall = {

};

//Klasa budynku, 1- MainCastle, 2- Barracks, 3- House
class Building
{
    int cost;
    int sizex;
    int sizey;
    int health;
    int owner;  // 0 - South, 1 - North, 2 - BeyondTheWall
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
    MainCastle();
};

class Barracks : public Building
{
private:

    std::vector<UnitPrice> availableUnits;

public:
    Barracks();
    std::vector<UnitPrice> getAvailableUnits(){return availableUnits;};
    void RecruitUnit(std::string name);

};

class House : public Building
{
    private:
        int HousePopulation;
    public:
        House();
        //Usuwa populacje z królestwa po zniszczeniu domu
        void DeletePopulation(int amount);

};


#endif // BUILDING_H

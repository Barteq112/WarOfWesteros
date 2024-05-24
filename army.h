#ifndef ARMY_H
#define ARMY_H
#include <vector>

class Unit
{
private:
    int id;
    int health;
    int attackDamage;
    int speed;
public:
    Unit();
    Unit( int health, int attackDamage, int speed);
    int getHealth() {return health;}
    virtual void attack(Unit *unit);
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    void move();
};

// klasy dzidziczące po klasie Unit Giant, Infantry, Archer, Cavalry, Magician, Wolf, HeavyKnight
class Giant : public Unit
{

};

class Infantry : public Unit
{

};

class Archer : public Unit
{

};

class Cavalry : public Unit
{

};

class Magician : public Unit
{

};

class Wolf : public Unit
{

};

class HeavyKnight : public Unit
{

};



class Army
{
private:
    std::vector<Unit> *units;
public:
    Army();
    std::vector<Unit> getUnits() {return *units;}
    void addUnit();
    void removeUnit(Unit *unit);
};



#endif // ARMY_H

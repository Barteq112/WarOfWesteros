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
    public:
    Giant();
};

class Infantry : public Unit
{
    Infantry();
};

class Archer : public Unit
{
    Archer();
};

class Cavalry : public Unit
{
    Cavalry();
};

class Magician : public Unit
{
    Magician();
};

class Wolf : public Unit
{
    Wolf();
};

class HeavyKnight : public Unit
{
    HeavyKnight();
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

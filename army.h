#ifndef ARMY_H
#define ARMY_H
#include <vector>

class Unit
{
public:
    Unit();
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

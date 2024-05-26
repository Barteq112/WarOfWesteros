#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <memory>
// Stale wymiary jednostki

constexpr int unitSizeX =9;
constexpr int unitSizeY =9;



// Definicja klasy Unit
class Unit {
protected:
    int x;
    int y;
    int id;
    int health;
    int attackDamage;
    int speed;
    int range;
    int attackSpeed;
    int owner; // 0 - South, 1 - North, 2 - BeyondTheWall

public:
    Unit();
    Unit(int health, int attackDamage, int speed, int range, int attackSpeed, int id);
    int getID() const { return id; }
    int getHealth() const { return health; }
    int getOwner() const { return owner; }
    virtual void attack(std::shared_ptr<Unit> unit);
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    void move();
    virtual ~Unit() {}
};

// Klasy dziedziczące po klasie Unit
class Giant : public Unit {
public:
    Giant(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class Infantry : public Unit {
public:
    Infantry(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class Archer : public Unit {
public:
    Archer(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class Cavalry : public Unit {
public:
    Cavalry(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class Magician : public Unit {
public:
    Magician(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class Wolf : public Unit {
public:
    Wolf(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

class HeavyKnight : public Unit {
public:
    HeavyKnight(int id);
    void attack(std::shared_ptr<Unit> unit) override;
};

// Definicja klasy Army
class Army {
private:
    std::vector<std::shared_ptr<Unit>> units;

public:
    Army();
    std::vector<std::shared_ptr<Unit>> getUnits() const { return units; }
    void addUnitToList(std::shared_ptr<Unit> unit);
    void removeUnitFromList(std::shared_ptr<Unit> unit);
    int checkLastID() const;
};

#endif // ARMY_H

#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <memory>
// Stale wymiary jednostki

constexpr int unitSizeX =17;
constexpr int unitSizeY =17;





class Map;

// Definicja klasy Unit
class Unit {
protected:
    int x;
    int y;
    int health;
    int attackDamage;
    int speed;
    int range;
    int attackSpeed;
    int type; //--typy jednostek--- 0 - Giant, 1 - Infantry, 2 - Archer, 3 - Cavalry, 4 - Magician, 5 - Wolf, 6 - HeavyKnight
    int owner; // 0 - South, 1 - North, 2 - BeyondTheWall
    bool inMotion;

public:
    Unit(){this->inMotion = false;};
    Unit(int health, int attackDamage, int speed, int range, int attackSpeed, int type);
    void setOwner(int owner) { this->owner = owner; }
    int getHealth() { return health; }
    int getOwner() { return owner; }
    virtual void attack(std::shared_ptr<Unit> unit);
    void setX (int x) { this->x = x; }
    void setY (int y) { this->y = y; }
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    void move(Map* mapa, int goalX, int goalY);
    std::vector<std::pair<int, int>> getPossibleMoves(int x, int y) const;

    virtual ~Unit() {}
};

// Klasy dziedziczące po klasie Unit
class Giant : public Unit {
public:
    Giant();
    void attack(std::shared_ptr<Unit> unit) override;
};

class Infantry : public Unit {
public:
    Infantry();
    void attack(std::shared_ptr<Unit> unit) override;
};

class Archer : public Unit {
public:
    Archer();
    void attack(std::shared_ptr<Unit> unit) override;
};

class Cavalry : public Unit {
public:
    Cavalry();
    void attack(std::shared_ptr<Unit> unit) override;
};

class Magician : public Unit {
public:
    Magician();
    void attack(std::shared_ptr<Unit> unit) override;
};

class Wolf : public Unit {
public:
    Wolf();
    void attack(std::shared_ptr<Unit> unit) override;
};

class HeavyKnight : public Unit {
public:
    HeavyKnight();
    void attack(std::shared_ptr<Unit> unit) override;
};

// Definicja klasy Army
class Army {
private:
    int owner;
    std::vector<std::shared_ptr<Unit>> units;

public:
    Army();
    std::vector<std::shared_ptr<Unit>> getUnits() { return units; }
    void addUnitToList(std::shared_ptr<Unit> unit);
    void removeUnitFromList(std::shared_ptr<Unit> unit);
    void setOwner(int owner) { this->owner = owner; }

};




#endif // ARMY_H

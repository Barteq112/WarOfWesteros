#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <memory>
// Stale wymiary jednostki

constexpr int unitSizeX =1;
constexpr int unitSizeY =1;





class Map;

// Definicja klasy Unit
class Unit {
protected:
    int x;
    int y;
    int destX;
    int destY;
    int maxHealth;
    int health;
    int attackDamage;
    int speed;
    int range;
    int attackSpeed;
    int type; //--typy jednostek--- 0 - Giant, 1 - Infantry, 2 - Archer, 3 - Cavalry, 4 - Magician, 5 - Wolf, 6 - HeavyKnight
    int owner; // 0 - South, 1 - North, 2 - BeyondTheWall

public:
    Unit();
    Unit(int health, int attackDamage, int speed, int range, int attackSpeed, int type);
    void setOwner(int owner) { this->owner = owner; }
    int getHealth() { return health; }
    int getOwner() { return owner; }
    int getX() { return x; }
    int getY() { return y; }
    int getDestX() { return destX; }
    int getDestY() { return destY; }
    virtual void attack(Map *map);
    void setX (int x) { this->x = x; }
    void setY (int y) { this->y = y; }
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    void move(Map* mapa);
    bool inMotion();
    void setDestination(int x, int y)
    {
        this->destX = x;
        this->destY = y;
    }

    virtual ~Unit() {}
};

// Klasy dziedziczące po klasie Unit
class Giant : public Unit {
public:
    Giant();
    void attack(Map *map) override;
};

class Infantry : public Unit {
public:
    Infantry();
    void attack(Map *map) override;
};

class Archer : public Unit {
public:
    Archer();
    void attack(Map *map) override;
};

class Cavalry : public Unit {
public:
    Cavalry();
    void attack(Map *map) override;
};

class Magician : public Unit {
public:
    Magician();
    void attack(Map *map) override;
};

class Wolf : public Unit {
public:
    Wolf();
    void attack(Map *map) override;
};

class HeavyKnight : public Unit {
public:
    HeavyKnight();
    void attack(Map *map) override;
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

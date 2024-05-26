#include "army.h"

Army::Army() {}

int Army::checkLastID() const {
    //Sprawdza ostatnie ID jednostki
    if (units.size() == 0) {
        return 0;
    }
    else {
        return units.back()->getID();
    }
}

Unit::Unit( int health, int attackDamage, int attackSpeed, int Range, int speed, int id) {
    this->health = health;
    this->attackDamage = attackDamage;
    this->speed = speed;
    this->range = Range;
    this->attackSpeed = attackSpeed;
    this->id = id;
}

void Unit::increaseHealth(int amount) {
    health += amount;
}

void Unit::decreaseHealth(int amount) {
    health -= amount;
}
void Unit::attack(std::shared_ptr<Unit> unit){} ;




//Konstruktor jednostek, inicjalizacja wartości początkowych -- health, attackDamage, attackSpeed, Range, speed, id

Giant::Giant(int id) : Unit(300, 30, 1, 2, 1,id){};

Infantry::Infantry(int id) : Unit(150, 30, 3, 3, 3,id){};

Archer::Archer(int id) : Unit(80, 20, 5, 9, 4,id){};

Cavalry::Cavalry(int id) : Unit(200, 40, 2, 5, 6,id){};

Magician::Magician(int id) : Unit(300, 50, 2, 3, 1,id){};

Wolf::Wolf(int id) : Unit(300, 50, 2, 3, 1,id){};

HeavyKnight::HeavyKnight(int id) : Unit(300, 50, 2, 3, 1,id){};


//Atak poszczególnych jednostek

void Giant::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void Infantry::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void Archer::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void Cavalry::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void Magician::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void Wolf::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}

void HeavyKnight::attack(std::shared_ptr<Unit> unit) {
    unit->decreaseHealth(attackDamage);
}



//Dodanie jednostki do armii

void Army::addUnitToList(std::shared_ptr<Unit> unit) {
    units.push_back(unit);
}


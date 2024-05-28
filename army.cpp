#include "army.h"

Army::Army() {}



Unit::Unit( int health, int attackDamage, int attackSpeed, int Range, int speed, int type) {
    this->health = health;
    this->attackDamage = attackDamage;
    this->speed = speed;
    this->range = Range;
    this->attackSpeed = attackSpeed;
    this->type = type;
}

void Unit::increaseHealth(int amount) {
    health += amount;
}

void Unit::decreaseHealth(int amount) {
    health -= amount;
}

void Unit::move()
{

}
void Unit::attack(std::shared_ptr<Unit> unit){} ;




//Konstruktor jednostek, inicjalizacja wartości początkowych -- health, attackDamage, attackSpeed, Range, speed, id

Giant::Giant() : Unit(300, 30, 1, 2, 1, 0){};

Infantry::Infantry() : Unit(150, 30, 3, 3, 3, 1){};

Archer::Archer() : Unit(80, 20, 5, 9, 4, 2){};

Cavalry::Cavalry() : Unit(200, 40, 2, 5, 6, 3){};

Magician::Magician() : Unit(300, 50, 2, 3, 1, 4){};

Wolf::Wolf() : Unit(300, 50, 2, 3, 1, 5){};

HeavyKnight::HeavyKnight() : Unit(300, 50, 2, 3, 1, 6){};


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


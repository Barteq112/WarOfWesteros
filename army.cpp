#include "army.h"
#include "map.h"
#include "game.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>  // Include queue for A* algorithm
#include <unordered_set>  // Dodano unordered_set do śledzenia odwiedzonych węzłów

//-------------------------------Astar--------------------------------------------

struct Node {
    int x, y;
    int gScore, hScore, fScore;
    Node* parent;

    Node(int x, int y) : x(x), y(y), gScore(0), hScore(0), fScore(0), parent(nullptr) {}

    bool operator<(const Node& other) const {
        return fScore > other.fScore;
    }

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    struct HashFunction {
        size_t operator()(const Node& node) const {
            return std::hash<int>()(node.x) ^ std::hash<int>()(node.y);
        }
    };
};

std::vector<std::pair<int, int>> AStar(Map* map, int startX, int startY, int goalX, int goalY) {
    std::priority_queue<Node> openSet;
    std::unordered_set<Node, Node::HashFunction> closedSet;

    Node start(startX, startY);
    start.gScore = 0;
    start.hScore = abs(startX - goalX) + abs(startY - goalY);
    start.fScore = start.gScore + start.hScore;
    openSet.push(start);

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goalX && current.y == goalY) {
            std::vector<std::pair<int, int>> path;
            for (Node* node = &current; node; node = node->parent) {
                path.push_back(std::make_pair(node->x, node->y));
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet.insert(current);

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if ((dx == 0 && dy == 0) || (abs(dx) == abs(dy) && !map->getTile(current.x + dx, current.y + dy)->getIsAvailable())) {
                    continue;
                }

                int neighborX = current.x + dx;
                int neighborY = current.y + dy;

                if (neighborX >= 0 && neighborX < map->getMapWidth() && neighborY >= 0 && neighborY < map->getMapHeight() && map->getTile(neighborX, neighborY)->getIsAvailable()) {
                    Node neighbor(neighborX, neighborY);
                    neighbor.gScore = current.gScore + 1;
                    neighbor.hScore = abs(neighborX - goalX) + abs(neighborY - goalY);
                    neighbor.fScore = neighbor.gScore + neighbor.hScore;
                    neighbor.parent = new Node(current);

                    if (closedSet.find(neighbor) == closedSet.end()) {
                        openSet.push(neighbor);
                    }
                }
            }
        }
    }

    return std::vector<std::pair<int, int>>();
}


//-----------------------------Klasa Army----------------------------------
Army::Army() {}

void Army::removeUnitFromList(int x, int y)
{

    auto unit = map->getTile(x, y)->getUnit();
    if (unit == nullptr)
    {
        return;
    }


    for (auto it = units.begin(); it != units.end(); ++it)
    {

        if ((*it)->getX() == x && (*it)->getY() == y)
        {

            units.erase(it);
            return;
        }
    }
}



//-----------------------------Klasa Unit----------------------------------

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
    if (health > maxHealth) {
        health = maxHealth;
    }
}

void Unit::decreaseHealth(int amount, Game *game) {
    health -= amount;
    if (health <= 0) {
        removeUnit(game);
    }
}

void Unit::move(Map* map) {
    if (x == destX && y == destY) {
        return;
    }
    // sprawdzenie czy docelowe pole jest dostępne, jeśli nie to szukamy najbliższego wolnego pola
    if(map->getTile(destX, destY)->getIsAvailable() == false) {
        auto[tmpX,tmpy] = map->findClosestFreeTile(destX, destY,unitSizeX,unitSizeY);
        destX = tmpX;
        destY = tmpy;
    }
    auto path = AStar(map, x, y, destX, destY);
    // jeśli ścieżka jest pusta, to cel nie jest osiągalny, więc nie ruszamy jednostki
    if(path.empty()) {
        destX = x;
        destY = y;
        return;
    }
    // poruszanie się zgodnie z wyznaczoną ścieżką
    auto unit = map->getTile(x, y)->getUnit();
    map->getTile(x, y)->setUnit(nullptr);
    this->setX(path[1].first);
    this->setY(path[1].second);
    map->getTile(x, y)->setUnit(unit);
}

bool Unit::inMotion()
{
    return x != destX || y != destY;
}

void Unit::removeUnit(Game* game)
{
    switch(owner)
    {
        case 0:
            game->getKingdomSouth()->getArmy().removeUnitFromList(x, y);
            break;
        case 1:
            game->getKingdomNorth()->getArmy().removeUnitFromList(x, y);
            break;
        case 2:
            game->getKingdomBeyondTheWall()->getArmy().removeUnitFromList(x, y);
            break;
    }


    auto map = game->getMap();
    map->getTile(x, y)->setUnit(nullptr);
    delete this;

}








void Unit::attack(Game *game){} ;




//Konstruktor jednostek, inicjalizacja wartości początkowych -- health, attackDamage, attackSpeed, Range, speed, id

Giant::Giant() : Unit(300, 30, 1, 2, 1, 0){maxHealth = health;};

Infantry::Infantry() : Unit(150, 30, 3, 3, 3, 1){maxHealth = health;};

Archer::Archer() : Unit(80, 20, 5, 9, 4, 2){maxHealth = health;};

Cavalry::Cavalry() : Unit(200, 40, 2, 5, 6, 3){maxHealth = health;};

Magician::Magician() : Unit(300, 50, 2, 3, 1, 4){maxHealth = health;};

Wolf::Wolf() : Unit(300, 50, 2, 3, 1, 5){maxHealth = health;};

HeavyKnight::HeavyKnight() : Unit(300, 50, 2, 3, 1, 6){maxHealth = health;};


//Atak poszczególnych jednostek

void Giant::attack(Game *game) {
    auto map = game->getMap();
    if(inMotion())
        return;
    //Pobiera wrogie jednostki w zasięgu i zadaje im obrażenia
    auto units = map->getEnemiesInRange(x, y, range, owner);
    for (auto unit : units) {
        unit->decreaseHealth(attackDamage,game);
    }
    if(units.empty())
    {
        //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }
}

void Infantry::attack(Game *game) {
    auto map = game->getMap();
    if(inMotion())
        return;
    //Pobiera najbliższego woga i zadaje dmg w zależności od ilości hp
    auto unit = map->getClosestEnemy(x, y,range, owner);
    if(unit != nullptr)
    {
        int baseDamage = attackDamage/2;
        int Dammage = baseDamage + attackDamage/2*(health/maxHealth);
        unit->decreaseHealth(Dammage,game);
    }
    else
    {
      //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }
}

void Archer::attack(Game *game) {
    auto map = game->getMap();
    if(inMotion())
        return;
    //Prosty atak
    auto unit = map->getClosestEnemy(x, y,range, owner);
    if(unit != nullptr)
    {
        unit->decreaseHealth(attackDamage,game);
    }
    else
    {
        //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }
}

void Cavalry::attack(Game *game) {
    auto map = game->getMap();
    //jeżeli w ruchu zadaje 50% obrażeń
    int Dammage;
    if(inMotion())
        Dammage = attackDamage/2;
    else
        Dammage = attackDamage;

    auto unit = map->getClosestEnemy(x, y,range, owner);
    if(unit != nullptr)
    {
        unit->decreaseHealth(Dammage,game);
    }
    else
    {
        //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }

}

void Magician::attack(Game *game) {
    auto map = game->getMap();
    if(inMotion())
        return;
    //Pobiera listę sojuszników i ich leczy
    auto units = map->getUnitsInRange(x, y, range, owner);
    for (auto unit : units) {
        unit->increaseHealth(attackDamage);
    }
}

void Wolf::attack(Game *game) {
    auto map = game->getMap();
    //Może atakwać w ruchu
    auto unit = map->getClosestEnemy(x, y,range, owner);
    if(unit != nullptr)
    {
        unit->decreaseHealth(attackDamage,game);
    }
    else
    {
        //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }
}

void HeavyKnight::attack(Game *game) {
    auto map = game->getMap();
    if(inMotion())
        return;
    //Ma 50% szans na podwójny atak
    auto unit = map->getClosestEnemy(x, y,range, owner);
    if(unit != nullptr)
    {
        unit->decreaseHealth(attackDamage,game);
        if(rand()%2 == 0)
            unit->decreaseHealth(attackDamage,game);
    }
    else
    {
        //Jeżeli nie ma wroga w zasięgu atakuję najbliższy wrogi budynek
        auto building = map->getClosestEnemyBuilding(x,y,range,owner);
        if(building != nullptr)
        {
            building->decreaseHealth(attackDamage/2,game);
        }
    }
}



//Dodanie jednostki do armii

void Army::addUnitToList(std::shared_ptr<Unit> unit) {
    units.push_back(unit);
}







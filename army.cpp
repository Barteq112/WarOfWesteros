#include "army.h"
#include "map.h"
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
}

void Unit::decreaseHealth(int amount) {
    health -= amount;
}

void Unit::move(Map* map, int goalX, int goalY) {
    if (x == goalX && y == goalY) {
        return;
    }
    auto path = AStar(map, x, y, goalX, goalY);
    // poruszanie się zgodnie z wyznaczoną ścieżką

    auto unit = map->getTile(x, y)->getUnit();
    map->getTile(x, y)->setUnit(nullptr);
    this->setX(path[1].first);
    this->setY(path[1].second);
    std::cout<<x<<" "<<y<<std::endl;
    map->getTile(x, y)->setUnit(unit);
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







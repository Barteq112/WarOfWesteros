#include "army.h"
#include "map.h"
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <memory>
#include <iostream>
//----------------------------------------------Algorytm A*-----------------------------------------------------
// Definicja klasy Node
// Definicja klasy Node
class Node {
public:
    int x, y;
    int g; // Koszt od startu do tego węzła
    int h; // Heurystyczny koszt do celu
    int f; // Całkowity koszt (g + h)
    Node* parent;

    Node(int x, int y, Node* parent = nullptr) : x(x), y(y), g(0), h(0), f(0), parent(parent) {}

    void calculateHeuristic(int goalX, int goalY) {
        h = std::abs(goalX - x) + std::abs(goalY - y); // Manhattan distance
    }

    void calculateTotalCost() {
        f = g + h;
    }
};

// Funktor do porównywania węzłów w kolejce priorytetowej
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};



std::pair<int, int> findFirstMoveAStar(Map *mapa,
                                       int startX, int startY, int goalX, int goalY,
                                       int unitSizeX, int unitSizeY) {
    auto map = mapa->getAvailableTiles();
    int width = map.size();
    int height = map[0].size();
    std::cout<<startX<<startY<<std::endl;
    // Sprawdzenie, czy mapa nie jest pusta
    if (width == 0 || height == 0) {
        std::cerr << "Map dimensions are invalid: width or height is zero\n";
        return {-1, -1};
    }
    auto unit = mapa->getTile(startX, startY)->getUnit();
    // Sprawdzenie poprawności startowej i końcowej pozycji
    if ( !mapa->placeIsAvailableForUnit(goalX,goalY,unitSizeX,unitSizeY,unit)) {
        std::cerr << "Goal position is not available\n";
        return {-1, -1};
    }


    // Inicjalizacja zbioru zamkniętego
    std::vector<std::vector<bool>> closedSet(width, std::vector<bool>(height, false)); // Zbiór odwiedzonych węzłów
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet; // Priorytetowa kolejka otwartych węzłów

    // Tworzenie węzła startowego
    Node* startNode = new Node(startX, startY);
    startNode->calculateHeuristic(goalX, goalY);
    startNode->calculateTotalCost();
    openSet.push(startNode);

    while (!openSet.empty()) {
        // Pobieranie węzła z najmniejszym kosztem f z priorytetowej kolejki
        Node* current = openSet.top();
        openSet.pop();

        // Logowanie bieżącej pozycji
        std::cerr << "Processing node at (" << current->x << ", " << current->y << ")\n";

        // Sprawdzanie, czy bieżący węzeł jest w granicach mapy
        if (current->x < 0 || current->x >= width || current->y < 0 || current->y >= height) {
            std::cerr << "Node out of bounds: (" << current->x << ", " << current->y << ")\n";
            delete current;
            continue;
        }

        // Jeśli dotarliśmy do celu, prześledźmy ścieżkę do początku, aby znaleźć pierwszy ruch
        if (current->x == goalX && current->y == goalY) {
            Node* pathNode = current;
            while (pathNode->parent && pathNode->parent->parent) {
                pathNode = pathNode->parent;
            }
            std::pair<int, int> firstMove = {pathNode->x, pathNode->y};
            // Zwolnienie pamięci
            while (current) {
                Node* parent = current->parent;
                delete current;
                current = parent;
            }
            return firstMove;
        }

        // Oznaczamy bieżący węzeł jako odwiedzony
        closedSet[current->x][current->y] = true;

        // Generujemy następników bieżącego węzła
        static const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (const auto& direction : directions) {
            int nx = current->x + direction.first;
            int ny = current->y + direction.second;

            // Sprawdzamy, czy nowe współrzędne są w granicach mapy i czy są dostępne
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !closedSet[nx][ny] && mapa->placeIsAvailableForUnit(nx, ny, unitSizeX, unitSizeY,unit)) {
                // Tworzenie nowego węzła
                Node* neighbor = new Node(nx, ny, current);
                neighbor->g = current->g + 1; // Koszt ruchu do sąsiada
                neighbor->calculateHeuristic(goalX, goalY); // Obliczamy heurystyczną wartość odległości do celu
                neighbor->calculateTotalCost(); // Obliczamy całkowity koszt f

                // Logowanie nowo utworzonego węzła
                std::cerr << "Adding neighbor node at (" << nx << ", " << ny << ") with f = " << neighbor->f << "\n";

                // Dodajemy sąsiada do priorytetowej kolejki
                openSet.push(neighbor);
            } else if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
                std::cerr << "Skipped out of bounds neighbor node at (" << nx << ", " << ny << ")\n";
            } else if (closedSet[nx][ny]) {
                std::cerr << "Skipped already closed neighbor node at (" << nx << ", " << ny << ")\n";
            } else if (!mapa->placeIsAvailable(nx, ny, unitSizeX, unitSizeY)) {
                std::cerr << "Skipped unavailable place for neighbor node at (" << nx << ", " << ny << ")\n";
            }
        }

        // Zwolnienie pamięci bieżącego węzła
        delete current;
    }

    // Jeśli nie udało się znaleźć pierwszego ruchu, zwracamy (-1, -1)
    std::cerr << "No valid path found\n";
    return {-1, -1};
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

void Unit::move(Map* mapa, int goalX, int goalY) {
    std::pair<int, int> nextPosition = findFirstMoveAStar(mapa, x, y, goalX, goalY, unitSizeX,unitSizeY);
    std::cout<<nextPosition.first<<nextPosition.second;
}




std::vector<std::pair<int, int> > Unit::getPossibleMoves(int x, int y) const
{
    std::vector<std::pair<int, int>> moves;
    for (int dx = -speed; dx <= speed; ++dx) {
        for (int dy = -speed; dy <= speed; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (abs(dx) + abs(dy) <= speed && nx >= 0 && ny >= 0) {
                moves.emplace_back(nx, ny);
            }
        }
    }
    return moves;

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







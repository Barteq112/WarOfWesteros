#include "map.h"
#include <queue>
#include <limits>
#include <cmath>
#include <utility>
#include <iostream>

//--------------------Klasa Map_tile----------------------------------

Map_tile::Map_tile()
{

    building = nullptr;
    unit = nullptr;
    isAvailable = true;
}

bool Map_tile::getIsAvailable()
{
    return isAvailable;
}

void Map_tile::setIsAvailable(bool available)
{
    this->isAvailable =available;
}

int Map_tile::getOwner()
{
    return owner;
}

void Map_tile::setOwner(int owner)
{
    this->owner = owner;
}

std::shared_ptr<Building> Map_tile::getBuilding()
{
    return building;
}

void Map_tile::setBuilding(std::shared_ptr<Building> building)
{
    this->building = building;
    this->setIsAvailable(false);
}

void Map_tile::removeBuilding()
{
    building = nullptr;
    this->setIsAvailable(true);
}

std::shared_ptr<Unit> Map_tile::getUnit()
{
    return unit;
}

void Map_tile::setUnit(std::shared_ptr<Unit> unit)
{
    this->unit = unit;
    this->setIsAvailable(false);
}

void Map_tile::removeUnit()
{
    unit = nullptr;
    this->setIsAvailable(true);
}



// --------------------Kalsa Map ------------------------------------




int Map::getMapWidth()
{
    return size_x;
}

int Map::getMapHeight()
{
    return size_y;
}

Map_tile* Map::getTile(int x, int y)
{
    //Sprawszenie czy w obrębi mapy
    if (x < 0 || x >= size_x || y < 0 || y >= size_y)
    {
        std::cout<<x<<" "<<y<<std::endl;
        std::cout<<"Error: getTile out of range\n";
        return nullptr;
    }
    return &map[x][y];
}

bool Map::placeIsAvailable(int x, int y, int sizex, int sizey) {

    if (x < 0 || y < 0 || x + sizex > getMapWidth() || y + sizey > getMapHeight()) {
        return false;
    }


    for (int i = x; i < x + sizex; i++) {
        for (int j = y; j < y + sizey; j++) {
            if (!getTile(i, j)->getIsAvailable()) {
                return false;
            }
        }
    }
    return true;
}

bool Map::placeIsAvailableForUnit(int x, int y, int sizex, int sizey, std::shared_ptr<Unit> unit)
{
    for (int i = x; i < x + sizex; i++) {
        for (int j = y; j < y + sizey; j++) {
            // Sprawdzamy, czy współrzędne są w granicach mapy
            if (i < 0 || i >= size_x || j < 0 || j >= size_y) {
                return false;
            }

            // Pobieramy kafelek z mapy
            Map_tile* tile = getTile(i, j);

            // Jeśli kafelek jest niedostępny i nie zawiera tej jednostki, zwracamy false
            if (!tile->getIsAvailable() && tile->getUnit() != unit) {
                return false;
            }
        }
    }
    return true;
}


bool Map::isYourPlace(int x, int y, int sizex, int sizey, int owner) {

    if (x < 0 || y < 0 || x + sizex > getMapWidth() || y + sizey > getMapHeight()) {
        return false;
    }


    for (int i = x; i < x + sizex; i++) {
        for (int j = y; j < y + sizey; j++) {
            if (getTile(i, j)->getOwner() != owner) {
                return false;
            }
        }
    }
    return true;
}



std::shared_ptr<Unit> Map::getClosestEnemy(int x, int y, int range, int owner)
{
    std::shared_ptr<Unit> closestEnemy = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    x = int(floor(x+0.5*unitSizeX));
    y = int(floor(y+0.5*unitSizeY));
    for (int i = std::max(0, x - range); i <= std::min(size_x-1, x + range); ++i)
    {
        for (int j = std::max(0, y - range); j <= std::min(size_y-1, y + range); ++j)
        {
            std::shared_ptr<Unit> unit = getTile(i, j)->getUnit();
            if (unit != nullptr && unit->getOwner() != owner)
            {
                double distance = std::sqrt((i - x) * (i - x) + (j - y) * (j - y));
                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestEnemy = unit;
                }
            }
        }
    }

    return closestEnemy;
}

std::vector<std::shared_ptr<Unit>> Map::getEnemiesInRange(int x, int y, int range, int owner)
{
    std::vector<std::shared_ptr<Unit>> enemiesInRange;
    x = int(floor(x+0.5*unitSizeX));
    y = int(floor(y+0.5*unitSizeY));
    for (int i = std::max(0, x - range); i <= std::min(size_x - 1, x + range); ++i)
    {
        for (int j = std::max(0, y - range); j <= std::min(size_y - 1, y + range); ++j)
        {
            std::shared_ptr<Unit> unit = getTile(i, j)->getUnit();
            if (unit != nullptr && unit->getOwner() != owner)
            {
                double distance = std::sqrt((i - x) * (i - x) + (j - y) * (j - y));
                if (distance <= range)
                {
                    enemiesInRange.push_back(unit);
                }
            }
        }
    }

    return enemiesInRange;
}

std::vector<std::shared_ptr<Unit>> Map::getUnitsInRange(int x, int y, int range, int owner) {
    std::vector<std::shared_ptr<Unit>> unitsInRange;
    x = int(floor(x+0.5*unitSizeX));
    y = int(floor(y+0.5*unitSizeY));

    for (int i = std::max(0, x - range); i <= std::min(size_x - 1, x + range); ++i) {
        for (int j = std::max(0, y - range); j <= std::min(size_y - 1, y + range); ++j) {
            std::shared_ptr<Unit> unit = getTile(i, j)->getUnit();

            if (unit != nullptr && unit->getOwner() == owner) {
                double distance = std::sqrt((i - x) * (i - x) + (j - y) * (j - y));
                if (distance <= range) {
                    unitsInRange.push_back(unit);
                }
            }
        }
    }

    return unitsInRange;
}

std::shared_ptr<Building> Map::getClosestEnemyBuilding(int x, int y, int range, int owner) {
    std::shared_ptr<Building> closestEnemyBuilding = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    x = int(floor(x+0.5*unitSizeX));
    y = int(floor(y+0.5*unitSizeY));

    for (int i = std::max(0, x - range); i <= std::min(size_x - 1, x + range); ++i) {
        for (int j = std::max(0, y - range); j <= std::min(size_y - 1, y + range); ++j) {
            std::shared_ptr<Building> building = getTile(i, j)->getBuilding();

            if (building != nullptr && building->getOwner() != owner) {
                double distance = std::sqrt((i - x) * (i - x) + (j - y) * (j - y));
                if (distance < minDistance) {
                    minDistance = distance;
                    closestEnemyBuilding = building;
                }
            }
        }
    }

    return closestEnemyBuilding;
}

void Map::setBuildingOnMap(int x, int y, std::shared_ptr<Building> building)
{
    int sizex = building->getSizex();
    int sizey = building->getSizey();
    for(int i = x; i < x + sizex; i++)
    {
        for(int j = y; j < y + sizey; j++)
        {
            getTile(i,j)->setBuilding(building);
        }
    }
}

void Map::removeBuildingFromMap(int x, int y, std::shared_ptr<Building> building)
{
    int sizex = building->getSizex();
    int sizey = building->getSizey();
    for(int i = x; i < x + sizex; i++)
    {
        for(int j = y; j < y + sizey; j++)
        {
            getTile(i,j)->removeBuilding();
        }
    }
}

void Map::setUnitOnMap(int x, int y, std::shared_ptr<Unit> unit)
{

    for(int i = x; i < x + unitSizeX; i++)
    {
        for(int j = y; j < y + unitSizeY; j++)
        {
            getTile(i,j)->setUnit(unit);
        }
    }

}

void Map::removeUnitFromMap(int x, int y)
{


    for(int i = x; i < x + unitSizeX; i++)
    {
        for(int j = y; j < y + unitSizeY; j++)
        {
            getTile(i,j)->removeUnit();
        }
    }
}

std::pair<int, int> Map::findClosestFreeTile(int x, int y, int sizex, int sizey) {
    const int stepSize = 1;

    std::queue<std::pair<int, int>> tilesToCheck;
    tilesToCheck.push({x, y});

    std::vector<std::vector<bool>> visited(getMapWidth(), std::vector<bool>(getMapHeight(), false));
    visited[x][y] = true;

    int directions[4][2] = {{stepSize, 0}, {0, stepSize}, {-stepSize, 0}, {0, -stepSize}};

    while (!tilesToCheck.empty()) {
        auto [currentX, currentY] = tilesToCheck.front();

        tilesToCheck.pop();

        if (placeIsAvailable(currentX, currentY, sizex, sizey)) {
            return {currentX, currentY};
        }

        for (auto& dir : directions) {
            int newX = currentX + dir[0];
            int newY = currentY + dir[1];

            // Sprawdzamy, czy nowe współrzędne są w granicach mapy
            if (newX >= 0 && newY >= 0 && newX < getMapWidth() && newY < getMapHeight() && !visited[newX][newY]) {
                // Sprawdzamy, czy cały obszar (sizex x sizey) mieści się w granicach mapy
                if (newX + sizex <= getMapWidth() && newY + sizey <= getMapHeight()) {
                    tilesToCheck.push({newX, newY});
                    visited[newX][newY] = true;
                }
            }
        }
    }
    return {-1, -1};
}

std::pair<int, int> Map::findClosestFreeTile(int x, int y, int sizex, int sizey, int owner)
{
    const int stepSize = 1;

    std::queue<std::pair<int, int>> tilesToCheck;
    tilesToCheck.push({x, y});

    std::vector<std::vector<bool>> visited(getMapWidth(), std::vector<bool>(getMapHeight(), false));
    visited[x][y] = true;

    int directions[4][2] = {{stepSize, 0}, {0, stepSize}, {-stepSize, 0}, {0, -stepSize}};

    while (!tilesToCheck.empty()) {
        auto [currentX, currentY] = tilesToCheck.front();
        tilesToCheck.pop();




        if (placeIsAvailable(currentX, currentY, sizex, sizey) && isYourPlace(currentX, currentY, sizex, sizey,owner)) {
            return {currentX, currentY};
        }

        // Dodajemy sąsiednie kafelki do sprawdzenia
        for (auto& dir : directions) {
            int newX = currentX + dir[0];
            int newY = currentY + dir[1];

            // Sprawdzamy, czy nowe współrzędne są w granicach mapy
            if (newX >= 0 && newY >= 0 && newX < getMapWidth()-1 && newY < getMapHeight()-1 && !visited[newX][newY]) {
                // Sprawdzamy, czy cały obszar (sizex x sizey) mieści się w granicach mapy
                if (newX + sizex <= getMapWidth() && newY + sizey <= getMapHeight()) {
                    tilesToCheck.push({newX, newY});
                    visited[newX][newY] = true;
                }
            }
        }
    }
    return {-1, -1};
}

std::vector<std::vector<bool> > Map::getAvailableTiles()
{
    std::vector<std::vector<bool>> availableTiles(size_x, std::vector<bool>(size_y, false));
    for(int i = 0; i < size_x; i++)
    {
        for(int j = 0; j < size_y; j++)
        {
            availableTiles[i][j] = getTile(i,j)->getIsAvailable();
        }
    }
    return availableTiles;
}

std::pair<int, int> Map::checkCoordinates(int x, int y)
{
    //sprawdzenie czy współrzędne są w granicach mapy
    if(x < 0)
    {
        x = 0;
    }
    if(y < 0)
    {
        y = 0;
    }
    if(x >= size_x)
    {
        x = size_x-1;
    }
    if(y >= size_y)
    {
        y = size_y-1;
    }
    return std::make_pair(x,y);
}






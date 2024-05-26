#include "map.h"
#include <queue>
#include <limits>
#include <cmath>
#include <utility>

//--------------------Klasa Map_tile----------------------------------

Map_tile::Map_tile()
{
    owner = nullptr;
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

Kingdom* Map_tile::getOwner()
{
    return owner;
}

void Map_tile::setOwner(Kingdom* owner)
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


Map::Map(int size_x, int size_y)
{
    this->size_x = size_x;
    this->size_y = size_y;
    map.resize(size_x);
    for(int i = 0; i < size_x; i++)
    {
        map[i].resize(size_y);
    }
}

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
    return &map[x][y];
}

bool Map::placeIsAvailable(int x, int y, int sizex , int sizey)
{
    for(int i = x; i < x + sizex; i++)
    {
        for(int j = y; j < y + sizey; j++)
        {
            if(getTile(i,j)->getIsAvailable() == false)
            {
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
    for (int i = std::max(0, x - range); i <= std::min(size_x - 1, x + range); ++i)
    {
        for (int j = std::max(0, y - range); j <= std::min(size_y - 1, y + range); ++j)
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
    //standardowy rozmiar jednostki to 3x3
    int sizex =3, sizey =3;
    for(int i = x; i < x + sizex; i++)
    {
        for(int j = y; j < y + sizey; j++)
        {
            getTile(i,j)->setUnit(unit);
        }
    }

}

void Map::removeUnitFromMap(int x, int y)
{
    //standardowy rozmiar jednostki to 3x3

    for(int i = x; i < x + unitSizeX; i++)
    {
        for(int j = y; j < y + unitSizeY; j++)
        {
            getTile(i,j)->removeUnit();
        }
    }
}

std::pair<int, int> Map::findClosestFreeTile(int x, int y, int sizex, int sizey) {
    std::queue<std::pair<int, int>> tilesToCheck;
    tilesToCheck.push({x, y});

    std::vector<std::vector<bool>> visited(getMapWidth(), std::vector<bool>(getMapHeight(), false));
    visited[x][y] = true;

    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (!tilesToCheck.empty()) {
        auto [currentX, currentY] = tilesToCheck.front();
        tilesToCheck.pop();

        if (placeIsAvailable(currentX, currentY, sizex, sizey)) {
            return {currentX, currentY};
        }

        for (auto& dir : directions) {
            int newX = currentX + dir[0];
            int newY = currentY + dir[1];

            if (newX >= 0 && newY >= 0 && newX < getMapWidth() && newY < getMapHeight() && !visited[newX][newY]) {
                tilesToCheck.push({newX, newY});
                visited[newX][newY] = true;
            }
        }
    }

    return {-1, -1}; // Jeśli nie znaleziono wolnego miejsca
}





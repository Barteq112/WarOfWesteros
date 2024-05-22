#include "map.h"



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
    isAvailable =available;
}

Kingdom* Map_tile::getOwner()
{
    return owner;
}

void Map_tile::setOwner(Kingdom* owner)
{
    this->owner = owner;
}

Building* Map_tile::getBuilding()
{
    return building;
}

void Map_tile::setBuilding(Building* building)
{
    this->building = building;
    this->setIsAvailable(false);
}

void Map_tile::removeBuilding()
{
    building = nullptr;
    this->setIsAvailable(true);
}

Unit* Map_tile::getUnit()
{
    return unit;
}

void Map_tile::setUnit(Unit* unit)
{
    this->unit = unit;
    this->setIsAvailable(false);
}

void Map_tile::removeUnit()
{
    unit = nullptr;
    this->setIsAvailable(true);
}

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

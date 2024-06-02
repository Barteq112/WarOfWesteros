#include "building.h"
#include "game.h"
Building::Building() {}

void Building::removeBuilding(Game *game)
{
    switch (owner) {
    case 0: // South
        game->getKingdomSouth()->removeBuildingFromList(x,y);
        break;
    case 1: // North
        game->getKingdomNorth()->removeBuildingFromList(x,y);
        break;
    case 2: // BeyondTheWall
        game->getKingdomBeyondTheWall()->removeBuildingFromList(x,y);
        break;

    }
    auto map = game->getMap();
    //Usuwa budynek z mapy ze wszystkich kafelków i z listy budynków
    for (int i = 0; i < sizex; i++)
    {
        for (int j = 0; j < sizey; j++)
        {
            map->getTile(x + i, y + j)->removeBuilding();
        }
    }


}



void Building::decreaseHealth(int amount, Game *game)
{
    health -= amount;
    if (health <= 0)
    {
        removeBuilding(game);
    }
}

void Building::increaseHealth(int amount)
{
    health += amount;
    if (health > maxHealth)
    {
        health = maxHealth;
    }
}


Barracks::Barracks(){this->type = 1; this->sizex = barracksSizeX; this->sizey = barracksSizeY; this->health = 800;
    this->maxHealth = 800;
    std::vector<UnitPrice> unitPrices;
    switch (owner) {
    case 0: // South
        unitPrices = southUnitPrices;
        break;
    case 1: // North
        unitPrices = northUnitPrices;
        break;
    case 2: // BeyondTheWall
        unitPrices = beyondTheWallUnitPrices;
        break;
    }
    availableUnits = unitPrices;
}

void Barracks::RecruitUnit(int unitType, Game* game) {
    Army* army = nullptr;
    Kingdom* kingdom = nullptr;

    switch (owner) {
    case 0: // South
        army = &game->getKingdomSouth()->getArmy();
        kingdom = game->getKingdomSouth();
        break;
    case 1: // North
        army = &game->getKingdomNorth()->getArmy();
        kingdom = game->getKingdomNorth();
        break;
    case 2: // BeyondTheWall
        army = &game->getKingdomBeyondTheWall()->getArmy();
        kingdom = game->getKingdomBeyondTheWall();
        break;
    default:

        return;
    }

    Map* map = game->getMap();
    std::shared_ptr<Unit> unit = nullptr;
    switch(unitType)
    {
    case 0: // Giant
        unit = std::make_shared<Giant>();

        break;
    case 1: // Infantry
        unit = std::make_shared<Infantry>();
        break;
    case 2: // Archer
        unit = std::make_shared<Archer>();
        break;
    case 3: // Cavalry
        unit = std::make_shared<Cavalry>();
        break;
    case 4: // Magician
        unit = std::make_shared<Magician>();
        break;
    case 5: // Wolf
        unit = std::make_shared<Wolf>();
        break;
    case 6: // HeavyKnight
        unit = std::make_shared<HeavyKnight>();
        break;
    }
    if (unit == nullptr) {
        return;
    }
    int price;
    for (auto& unit : availableUnits) {
        if (unit.type == unitType) {
             price = unit.price;
        }
    }
    if (kingdom->getResources().getGold() < price) {
        return;
    }
    auto[xx,yy] = map->findClosestFreeTile(x+int(barracksSizeX/2),y+int(barracksSizeY/2),unitSizeX,unitSizeY);
    if(xx==-1)
    {
        return;
    }
    kingdom->getResources().decreaseGold(price);
    unit->setOwner(owner);
    army->addUnitToList(unit);
    map->setUnitOnMap(xx, yy, unit);
    unit->setX(xx);
    unit->setY(yy);
    unit->setDestination(xx,yy);

}

void MainCastle::upgradeCastle()
{
    level++;
    maxHealth += 200;
    health += 200;
}

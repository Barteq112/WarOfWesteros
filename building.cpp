#include "building.h"
#include "game.h"

Building::Building() {}

Barracks::Barracks(){this->type = 1; this->sizex = barracksSizeX; this->sizey = barracksSizeY; this->health = 800;
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
    kingdom->getResources().decreaseGold(price);
    unit->setOwner(owner);
    army->addUnitToList(unit);
    auto[xx,yy] = map->findClosestFreeTile(x,y,unitSizeX,unitSizeY);
    map->setUnitOnMap(xx, yy, unit);

}

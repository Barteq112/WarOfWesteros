#include "kingdom.h"
#include "game.h"
#include "building.h"

Kingdom::Kingdom() : resources(100,100) {}

void Kingdom::buildMainCastle(int x, int y, Game *gra)
{
    if(gra->getMap()->placeIsAvailable(x,y,mainCastleSizeX,mainCastleSizeY))
    {
        return;
    }
    std::shared_ptr<MainCastle> mainCastle = std::make_shared<MainCastle>();
    buildings.push_back(mainCastle);
    gra->getMap()->setBuildingOnMap(x,y,mainCastle);

}



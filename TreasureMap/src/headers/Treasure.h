#pragma once
#include "Tile.h"
class Treasure :
    public Tile
{
public:
    Treasure();
    Treasure(int amount);
    ~Treasure();

    std::string getName() override;
    const int getTreasureLeft();

    void gatherTreasure();

private:
    int m_amount;
};


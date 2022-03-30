#pragma once
#include "Tile.h"
class Mountain :
    public Tile
{
public:
    Mountain();
    ~Mountain();

    std::string getName() override;
};


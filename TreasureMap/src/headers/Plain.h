#pragma once
#include "Tile.h"
class Plain :
    public Tile
{
public:
    Plain();
    ~Plain();

    std::string getName() override;
};


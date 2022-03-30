#include "Tile.h"

Tile::Tile(bool walkable): m_walkable(walkable) { }

Tile::~Tile()
{
}

const bool Tile::isWalkable()
{
    return this->m_walkable;
}

#include "Treasure.h"

Treasure::Treasure() : Tile(true), m_amount(0) {}

Treasure::Treasure(int amount): Tile(true), m_amount(amount) {}

Treasure::~Treasure()
{
}

std::string Treasure::getName()
{
    return "T(" + std::to_string(this->m_amount) + ")";
}

const int Treasure::getTreasureLeft()
{
    return this->m_amount;
}

void Treasure::gatherTreasure()
{
    this->m_amount--;
}

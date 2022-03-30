#include "Mountain.h"

Mountain::Mountain() : Tile(false) {}

Mountain::~Mountain()
{
}

std::string Mountain::getName()
{
    return "M";
}

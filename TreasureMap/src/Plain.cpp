#include "Plain.h"

Plain::Plain() : Tile(true) {}

Plain::~Plain()
{
}

std::string Plain::getName()
{
    return ".";
}

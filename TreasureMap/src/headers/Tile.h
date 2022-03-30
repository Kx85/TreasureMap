#pragma once
#include <string>

class Tile
{
public:
	Tile(bool walkable);
	virtual ~Tile();
	virtual std::string getName() = 0;

	const bool isWalkable();

private:
	bool m_walkable;
};


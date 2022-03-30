#pragma once
#include "Tile.h"
#include "Plain.h"
#include <Vector>
#include <memory>

using Map = std::vector<std::vector<Tile*>>;

class TreasureMap
{
public:
	TreasureMap();
	TreasureMap(int column, int row);
	~TreasureMap();

	Tile* tileAt(int x, int y);
	const bool isColliding(int x, int y);

	void setTileAt(Tile* a, int row, int column);
	const std::string displayMap(bool noOutput);

	void insertAdventurer(Tile* a);

	bool isValideCoordinate(int column, int row);

	void processNextStep();
	bool hasMore();
private:

	int m_row;
	int m_column;
	Map m_map;
	std::vector<Tile*> m_adventurerList;
	bool m_more = true;
};


#include "TreasureMap.h"
#include "Adventurer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

TreasureMap::TreasureMap(): TreasureMap(1,1)
{
}

TreasureMap::TreasureMap(int column, int row): m_row(row), m_column(column)
{
	for (int i = 0; i < row; i++) {
		std::vector<Tile*> l_row;
		for (int k = 0; k < column; k++) {
			
			l_row.push_back(new Plain());
		}
		this->m_map.push_back(l_row);
	}
}

TreasureMap::~TreasureMap()
{
}

Tile* TreasureMap::tileAt(int column, int row)
{
	return this->m_map.at(row).at(column);
}

const bool TreasureMap::isColliding(int column, int row)
{
	return !(this->isValideCoordinate(column,row) && this->tileAt(column, row)->isWalkable());
}

void TreasureMap::setTileAt(Tile* a, int column, int row)
{
	this->m_map.at(row).at(column) = a;

}

const std::string TreasureMap::displayMap(bool noOutput)
{
	std::ostringstream l_r;
	for (const auto& l_row : this->m_map) {
		for (const auto& l_column : l_row) {
			l_r << std::left << std::setw(25) << l_column->getName() << " ";
		}
		l_r << std::endl;
	}

	if (!noOutput)
		std::cout << l_r.str();

	return l_r.str();
}

void TreasureMap::insertAdventurer(Tile* a)
{
	this->m_adventurerList.push_back((Adventurer*)a);
}

bool TreasureMap::isValideCoordinate(int column, int row)
{
	return (column < this->m_column && row < this->m_row && column >= 0 && row >= 0 && (this->tileAt(column, row)->getName() == "." || this->tileAt(column, row)->getName().at(0) == 'T')) ? true : false;
}


void TreasureMap::processNextStep()
{
	
	for (unsigned int i = 0; i < this->m_adventurerList.size(); i++) {
		Adventurer* p_a = (Adventurer*)this->m_adventurerList.at(i);

		if (!p_a->hasNextSequence()) {
			continue;
		}

		this->m_more = true;
		Adventurer::Position l_p(0,0);
		char next = p_a->next();
		switch (next) {
		case 'A':
			l_p = p_a->move();
			if (!this->isColliding(l_p.getColumn(), l_p.getRow())) {
				Tile* l_prev = p_a->getPreviousTile();
				Tile* l_new = this->tileAt(l_p.getColumn(), l_p.getRow());
				this->setTileAt(l_prev, p_a->getPosition().getColumn(), p_a->getPosition().getRow());
				p_a->storeTile(l_new);
				p_a->updatePosition(l_p);
				this->setTileAt(p_a, p_a->getPosition().getColumn(), p_a->getPosition().getRow());

				//Will only gather if tile is a treasure and has any left
				p_a->gatherTreasure();
			}
			continue;
		case 'D':
			p_a->turnRight();
			continue;
		case 'G':
			p_a->turnLeft();
			continue;
		}
	}
	
}

bool TreasureMap::hasMore()
{
	if (this->m_more) {
		this->m_more = !this->m_more;
		return true;
	}
	return false;
}

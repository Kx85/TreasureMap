#include "Adventurer.h"
#include "Plain.h"
#include <iostream>

Adventurer::Adventurer(std::string name, int treasureCount, Orientation orientation, std::string sequence, int column, int row) :
	Tile(false),
	m_name(name),
	m_treasureCout(treasureCount),
	m_orientation(orientation),
	m_pos(Adventurer::Position::Position(column, row)),
	m_previousTile(new Plain())
{
	Adventurer::setSequence(sequence);
}

Adventurer::~Adventurer()
{
}

const std::string Adventurer::getAName()
{
	return this->m_name;
}

void Adventurer::setAName(const std::string name)
{
	this->m_name = name;
}

void Adventurer::gatherTreasure()
{
	if (dynamic_cast<Treasure*> (this->m_previousTile) && ((Treasure * )this->m_previousTile)->getTreasureLeft() > 0) {
		((Treasure*)this->m_previousTile)->gatherTreasure();
		this->m_treasureCout++;
	}
}

const int Adventurer::treasureCount()
{
	return this->m_treasureCout;
}

Adventurer::Orientation Adventurer::getOrientation()
{
	return this->m_orientation;
}

void Adventurer::turnLeft()
{
	this->m_orientation = static_cast<Adventurer::Orientation>((static_cast<int>(this->m_orientation) + 3) % 4);
}

void Adventurer::turnRight()
{
	this->m_orientation = static_cast<Adventurer::Orientation>((static_cast<int>(this->m_orientation) + 1) % 4);
}

Adventurer::Position Adventurer::move()
{
	Adventurer::Position l_p = this->m_pos;
	int r = l_p.getRow();
	int c = l_p.getColumn();

	switch (this->m_orientation) {
	case Adventurer::Orientation::N:
		l_p.setRow(--r);
		break;
	case Adventurer::Orientation::E:
		l_p.setColumn(++c);
		break;
	case Adventurer::Orientation::S:
		l_p.setRow(++r);
		break;
	case Adventurer::Orientation::O:
		l_p.setColumn(--c);
		break;
	}

	return l_p;
}

std::string Adventurer::enum_to_string(const Adventurer::Orientation o)
{
	switch (o) {
	case Adventurer::Orientation::N:
		return "N";
	case Adventurer::Orientation::E:
		return "E";
	case Adventurer::Orientation::S:
		return "S";
	case Adventurer::Orientation::O:
		return "O";
	default:
		throw std::exception("Bad orientation");
	}
}

Adventurer::Orientation Adventurer::string_to_enum(const std::string s)
{
	static std::unordered_map<std::string, Orientation> const table = { {"N",Orientation::N}, {"E",Orientation::E}, {"S",Orientation::S}, {"O",Orientation::O}  };

	auto it = table.find(s);
	if (it != table.end()) return it->second;
	throw std::exception("Bad orientation");
}

Adventurer::Position Adventurer::getPosition()
{
	return this->m_pos;
}

void Adventurer::updatePosition(Position p)
{
	this->m_pos.updatePosition(p);
}

void Adventurer::setSequence(const std::string sequence)
{
	this->m_sequence = sequence;
	this->m_sequenceIt = this->m_sequence.begin();
}

bool Adventurer::hasNextSequence()
{
	bool result;
	if (this->m_sequenceIt != this->m_sequence.end()) {
		result = true;
	}
	else {
		result = false;
	}

	return result;
}

char Adventurer::next()
{
	return *(this->m_sequenceIt++);
}

Tile* Adventurer::getPreviousTile()
{
	return this->m_previousTile;
}

void Adventurer::storeTile(Tile* tile)
{
	this->m_previousTile = tile;
}


std::string Adventurer::getName()
{
	return "A(" + this->m_name + ")";
}

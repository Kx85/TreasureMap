#include "TMapReader.h"
#include "TreasureMap.h"
#include "Mountain.h"
#include "Treasure.h"
#include "Adventurer.h"
#include <string>
#include <sstream>

TMapReader::TMapReader(): m_filename("config\\input.itm") {}
TMapReader::TMapReader(const std::string& filename) : m_filename(filename)
{
}

TMapReader::~TMapReader()
{
}

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void processLine(std::string line, TreasureMap& map) {
	std::string l_line = line;

	l_line.erase(std::remove_if(l_line.begin(),l_line.end(),isspace), l_line.end());

	int l_column = -1, l_row = -1, l_treasure = -1;
	std::vector<std::string> out;
	const char delim = '-';

	switch (std::toupper(l_line.at(0))) {
	case 'C':
		tokenize(l_line, delim, out);
		l_column = std::stoi(out.at(1));
		l_row = std::stoi(out.at(2));

		map = TreasureMap(l_column, l_row);
		break;
	case 'M':
		tokenize(l_line, delim, out);
		l_column = std::stoi(out.at(1));
		l_row = std::stoi(out.at(2));

		if (map.isValideCoordinate(l_column, l_row)) {
			map.setTileAt(new Mountain(), l_column, l_row);
		} else {
			throw std::exception("Invalid mountain coordinates (Out of bounds)");
			
		}
		break;
	case 'T':
		tokenize(l_line, delim, out);
		l_column = std::stoi(out.at(1));
		l_row = std::stoi(out.at(2));
		l_treasure = std::stoi(out.at(3));

		if (map.isValideCoordinate(l_column, l_row)) {
			map.setTileAt(new Treasure(l_treasure), l_column, l_row);
		}
		else {
			throw std::exception("Invalid treasure coordinates (Out of bounds)");

		}
		break;

	case 'A':
		std::string l_name, l_sequence, l_orientation;
		tokenize(l_line, delim, out);
		l_name = out.at(1);
		l_column = std::stoi(out.at(2));
		l_row = std::stoi(out.at(3));
		l_orientation = out.at(4);
		l_sequence = out.at(5);

		if (map.isValideCoordinate(l_column, l_row)) {
			Tile* l_av = new Adventurer(l_name, 0, Adventurer::string_to_enum(l_orientation), l_sequence, l_column, l_row);
			map.setTileAt(l_av, l_column, l_row);
			map.insertAdventurer(l_av);
		}
		else {
			throw std::exception("Invalid adventurer");

		}
		break;
	}
}

void TMapReader::generateTMap(TreasureMap& map)
{
	std::string l_line;
	std::ifstream l_file;
	l_file.open(this->m_filename.c_str());

	try {
		std::getline(l_file, l_line);
		processLine(l_line, map);

		while (std::getline(l_file, l_line)) {
			processLine(l_line, map);
		}
	}
	catch (std::exception e) {
		throw std::exception("Wrong syntax");
	}

}

const std::string TMapReader::displayTMapFile()
{
	std::string l_line, l_result;
	std::ifstream l_file;
	l_file.open(this->m_filename);

	while (std::getline(l_file, l_line)) {
		l_result += (l_line + "\n");
	}

	l_file.close();
	return l_result;
}

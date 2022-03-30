#pragma once
#include "TreasureMap.h"
#include <iostream>
#include <fstream>
#include <exception>

class TMapReader
{

public:

	TMapReader();
	TMapReader(const std::string& filename);
	~TMapReader();

	void generateTMap(TreasureMap& map);
	const std::string displayTMapFile();

protected:
private:
	std::string m_filename;
};


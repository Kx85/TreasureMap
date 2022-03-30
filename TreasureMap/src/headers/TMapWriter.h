#pragma once
#include <iostream>
#include <fstream>
#include "TreasureMap.h"
class TMapWriter
{

public:

	TMapWriter();
	~TMapWriter();

	void writeTMap(TreasureMap& map);

protected:
private:
	std::string m_filename;
};


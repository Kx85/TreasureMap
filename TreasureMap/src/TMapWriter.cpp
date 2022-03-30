#include "TMapWriter.h"

TMapWriter::TMapWriter(): m_filename("output.omap")
{
}

TMapWriter::~TMapWriter()
{
}

void TMapWriter::writeTMap(TreasureMap& map)
{
	std::ofstream outfile(this->m_filename);
	outfile << map.displayMap(true);

	outfile.close();
}
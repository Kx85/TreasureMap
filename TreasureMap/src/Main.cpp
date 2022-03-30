#include "TMapReader.h"
#include "TMapWriter.h"
#include "TreasureMap.h"
#include <exception>

int main() {
	TMapReader* reader;
	TMapWriter* writer;
	TreasureMap map;
	try{
		reader = new TMapReader();
		writer = new TMapWriter();

		reader->generateTMap(map);
		std::cout << "File input (modify config/inpu.itm to change input file):" << std::endl;
		map.displayMap(false);

		while (map.hasMore()) {
			map.processNextStep();
		}

		std::cout << std::endl << "File Ouput after simlulation (saved as input.omap):" << std::endl;
		map.displayMap(false);
		writer->writeTMap(map);
		
	}
	catch (std::exception e) {
		std::cout << "Something went wrong : (" << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}
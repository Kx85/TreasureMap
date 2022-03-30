#include "TMapReader.h"
#include "TreasureMap.h"
#include "Treasure.h"
#include "Adventurer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int failed = 0;
int success = 0;

#define IS_TRUE(x) { if (!(x)) { std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; failed++; } else { std::cout << __FUNCTION__ << " OK " << std::endl; success++; } }
#define ASSERT(x,y) { if (x != y) { std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; failed++; } else { std::cout << __FUNCTION__ << " OK " << std::endl; success++; } }

void testSingleTile() {

	std::string l_filename = "testFiles\\testSingleTile.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());

	const std::string map = reader->displayTMapFile();

	ASSERT(reader->displayTMapFile(), "C - 1 - 1\n");

	delete reader;
}

void testSingleRowColumn() {
	std::string l_filename = "testFiles\\testSingleTile.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	std::ostringstream oss;
	oss << std::left << std::setw(25) << "." << " " << std::endl;
	ASSERT(map.displayMap(true), oss.str());

	delete reader;
}

void testSingleMountainTile() {

	std::string l_filename = "testFiles\\testSingleMountainTile.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);

	ASSERT(map.tileAt(0,0)->getName(), "M");

	delete reader;
}

void testBadMountainPosition() {

	std::string l_filename = "testFiles\\testBadMountainPosition.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	try {
		reader->generateTMap(map);
		IS_TRUE(false);
	}
	catch (std::exception e) {
		IS_TRUE(true);
	}

	delete reader;
}

void testMixedPlainAndMountain() {

	std::string l_filename = "testFiles\\testMixedPlainAndMountain.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	std::ostringstream oss;
	oss << std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "." << " " << std::endl
		<< std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "M" << " " << std::endl;

	ASSERT(map.displayMap(true), oss.str());

	delete reader;
}

void testMixedPlainAndMultipleMountain() {

	std::string l_filename = "testFiles\\testMixedPlainAndMultipleMountain.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	std::ostringstream oss;
	oss << std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "." << " " << std::setw(25) << "." << " " << std::endl
		<< std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "M" << " " << std::setw(25) << "." << " " << std::endl
		<< std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "." << " " << std::setw(25) << "." << " " << std::endl
		<< std::left << std::setw(25) << "." << " " << std::left << std::setw(25) << "M" << " " << std::setw(25) << "M" << " " << std::endl;

	ASSERT(map.displayMap(true), oss.str());

	delete reader;
}

void testDuplicatedTiles() {

	std::string l_filename = "testFiles\\testDuplicatedTiles.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	try {
		reader->generateTMap(map);
		IS_TRUE(false);
	}
	catch (std::exception e) {
		IS_TRUE(true);
	}


	delete reader;
}

void testTreasureTile() {

	std::string l_filename = "testFiles\\testTreasureTile.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);

	Treasure* t = (Treasure*)map.tileAt(2, 3);
	ASSERT(t->getName(), "T(1)");
	ASSERT(t->getTreasureLeft(), 1);
	t->gatherTreasure();
	ASSERT(t->getTreasureLeft(), 0);

	delete reader;
}

void testAdventurerTile() {

	std::string l_filename = "testFiles\\testAdventurerTile.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);

	Adventurer* t = (Adventurer*)map.tileAt(0, 0);
	ASSERT(t->getName(), "A(Lara)");
	ASSERT(t->getAName(), "Lara");
	ASSERT(t->enum_to_string(t->getOrientation()), "S");
	ASSERT(t->next(), 'A');
	ASSERT(t->hasNextSequence(), true);
	ASSERT(t->next(), 'D');
	ASSERT(t->hasNextSequence(), true);
	ASSERT(t->next(), 'A');
	ASSERT(t->hasNextSequence(), true);
	ASSERT(t->next(), 'D');
	ASSERT(t->hasNextSequence(), true);
	ASSERT(t->next(), 'A');
	ASSERT(t->hasNextSequence(), false);
	ASSERT(t->isWalkable(), false);
	ASSERT(t->treasureCount(), 0);
	ASSERT(map.tileAt(0, 0)->getName(), "A(Lara)");

	delete reader;
}

void testAdventurerRightTurnMouvement() {
	std::string l_filename = "testFiles\\testAdventurerRightTurnMouvement.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	Adventurer* t = (Adventurer*)map.tileAt(0, 0);

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "E");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 0).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "S");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 0).getRow());


	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "S");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "O");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "O");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "N");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "N");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 0).getRow());

	delete reader;
}

void testAdventurerLeftTurnMouvement() {
	std::string l_filename = "testFiles\\testAdventurerLeftTurnMouvement.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	Adventurer* t = (Adventurer*)map.tileAt(0, 0);

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "S");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "E");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 1).getRow());


	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "E");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "N");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 1).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 1).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "N");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 0).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "O");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 0).getRow());

	map.processNextStep();
	ASSERT(t->enum_to_string(t->getOrientation()), "O");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(0, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(0, 0).getRow());

	delete reader;
}

void testAdventurerGatherTreasure() {
	std::string l_filename = "testFiles\\testAdventurerGatherTreasure.itm";
	TMapReader* reader = new TMapReader(l_filename.c_str());
	TreasureMap map;

	reader->generateTMap(map);
	Adventurer* t = (Adventurer*)map.tileAt(0, 0);
	Treasure* tr = (Treasure*)map.tileAt(1, 0);
	ASSERT(tr->getTreasureLeft(), 2);

	map.processNextStep();
	ASSERT(tr->getTreasureLeft(), 1);
	ASSERT(t->treasureCount(), 1);
	ASSERT(t->enum_to_string(t->getOrientation()), "E");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(1, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(1, 0).getRow());

	map.processNextStep();
	ASSERT(tr->getTreasureLeft(), 1);
	ASSERT(t->enum_to_string(t->getOrientation()), "E");
	ASSERT(t->getPosition().getColumn(), Adventurer::Position(2, 0).getColumn());
	ASSERT(t->getPosition().getRow(), Adventurer::Position(2, 0).getRow());



	delete reader;
}


int main() {
	/*
	Test Reader consistency with a single tile
	File content:
	C - 1 - 1
	*/
	try {
		testSingleTile();
	}
	catch (std::exception e) {
		std::cout << "testSingleTile.itm not found NOK" << std::endl;
		failed++;
	}
	try {
		testSingleRowColumn();
	}
	catch (std::exception e) {
		std::cout << "testSingleRowColumn.itm not found NOK" << std::endl;
		failed++;
	}


	/*
	Test Reader consistency with a single Mountain tile
	File content:
	C - 1 - 1
	M - 1 - 1
	*/
	try {
		testSingleMountainTile();
	}
	catch (std::exception e) {
		std::cout << "testSingleMountainTile.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with a bad Mountain position tile
	File content:
	C - 1 - 1
	M - 2 - 1
	*/
	try {
		testBadMountainPosition();
	}
	catch (std::exception e) {
		std::cout << "testBadMountainPosition.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with a mixed set of tiles (Plains and Mountains)
	File content:
	C - 2 - 2
	M - 1 - 1
	*/
	try {
		testMixedPlainAndMountain();
	}
	catch (std::exception e) {
		std::cout << "testMixedPlainAndMountain.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with a single Mountain tile
	File content:
	C - 3 - 4
	M - 1 - 1
	M - 2 - 3
	M - 1 - 4
	*/
	try {
		testMixedPlainAndMultipleMountain();
	}
	catch (std::exception e) {
		std::cout << "testMixedPlainAndMultipleMountain.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with a duplicated Mountain tile
	File content:
	C - 3 - 4
	M - 1 - 1
	M - 1 - 1
	*/
	try {
		testDuplicatedTiles();
	}
	catch (std::exception e) {
		std::cout << "testDuplicatedTiles.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with a Treasure tile
	File content:
	C - 3 - 4
	T - 2 - 3 - 1
	*/
	try {
		testTreasureTile();
	}
	catch (std::exception e) {
		std::cout << "testTreasureTile.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test Reader consistency with an Adventurer tile
	File content:
	C - 1 - 1
    A - Lara - 0 - 0 - S - ADADA
	*/
	try {
		testAdventurerTile();
	}
	catch (std::exception e) {
		std::cout << "testAdventurerTile.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test consistency with an Adventurer tile
	File content:
	C - 1 - 1
	A - Biche - 0 - 0 - E - ADADADA

	Loop:
	1 -> 2
	/\   ||
	||   \/
	4 <- 3

	*/
	try {
		testAdventurerRightTurnMouvement();
	}
	catch (std::exception e) {
		std::cout << "testAdventurerRightTurnMouvement.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	Test consistency with an Adventurer tile
	File content:
	C - 2 - 2
    A - Biche - 0 - 0 - S - AGAGAGA

	Loop:
	1 <- 4
	||   /\
	\/   ||
	2 -> 3

	*/
	try {
		testAdventurerLeftTurnMouvement();
	}
	catch (std::exception e) {
		std::cout << "testAdventurerLeftTurnMouvement.itm not found NOK" << std::endl;
		failed++;
	}

	/*
	* Test consistency as an Adventurer steps
	* on a treasure tile and leaves it
	C - 3 - 1
	T - 1 - 0 - 2
	A - Jacques - 0 - 0 - E - AA
	*/
	try {
		testAdventurerGatherTreasure();
	}
	catch (std::exception e) {
		std::cout << "testAdventurerGatherTreasure.itm not found NOK" << std::endl;
		failed++;
	}

	double result = 100.0 * success / (success + failed);
	std::cout << std::endl << "Test passed: " << success << "/" << (success + failed) << " (" << std::fixed << std::setprecision(2) << result << "%)" << std::endl;
	
	system("PAUSE");

	return 0;
}
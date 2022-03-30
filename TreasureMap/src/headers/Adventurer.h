#pragma once
#include "Tile.h"
#include "Treasure.h"
#include <unordered_map>
class Adventurer :
    public Tile
{
public:
    class Position {
    public:
        Position(int c, int r) :m_column(c), m_row(r) {};
        int getColumn() { return this->m_column; }
        int getRow() { return this->m_row; }
        void setColumn(int column) { this->m_column = column; }
        void setRow(int row) { this->m_row = row; }
        void updatePosition(Position p) { this->m_column = p.getColumn(); this->m_row = p.getRow(); }
    private:
        int m_column;
        int m_row;
    };


    enum class Orientation {N, E, S, O};

    Adventurer(std::string name, int treasureCount, Orientation orientation, std::string sequence, int column, int row);
    ~Adventurer();

    const std::string getAName();
    void setAName(const std::string name);

    void gatherTreasure();
    const int treasureCount();

    Orientation getOrientation();
    void turnLeft();
    void turnRight();
    Position move();
    Position getPosition();
    void updatePosition(Position p);

    void setSequence(const std::string sequence);
    bool hasNextSequence();
    char next();

    Tile* getPreviousTile();
    void storeTile(Tile* tile);

    std::string enum_to_string(const Adventurer::Orientation o);
    static Adventurer::Orientation string_to_enum(const std::string s);

    std::string getName() override;

private:
    std::string m_name;
    int m_treasureCout = 0;
    Orientation m_orientation = Orientation::N;
    std::string m_sequence;
    std::string::iterator m_sequenceIt;
    Position m_pos;
    Tile* m_previousTile;
};


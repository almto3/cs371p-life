#ifndef Life_h
#define Life_h

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

class Cell;

class AbstractCell {
public:
	virtual Cell evolve(std::vector<Cell> neighbors) = 0;
	virtual void print(std::ostream& out) = 0;
	virtual AbstractCell* clone() const = 0;

	AbstractCell() : alive(false) {}

protected:
	bool alive;
};

class ConwayCell : public AbstractCell {
public:
	ConwayCell(const char& input);
	void print(std::ostream& out);
	Cell evolve(std::vector<Cell> neighbors);

	ConwayCell* clone() const;

protected:
	FRIEND_TEST(ConwayFixture, conway_construct1);
	FRIEND_TEST(ConwayFixture, conway_construct2);
};

/*class FredkinCell : public AbstractCell {
public:
	FredkinCell(const char& input);
	void print(std::ostream& out);
	Cell evolve(std::vector<Cell> neighbors);

	FredkinCell* clone() const;
private:
	int age;
};*/

class Cell {
public:
	AbstractCell *acell;

	Cell(AbstractCell* c) : acell(c) {}
	Cell(const Cell& c);
	~Cell();
	Cell& operator=(const Cell& rhs);
};

template <typename T>
class Life {
public:
	Life(std::istream& board);

	void print(std::ostream& out);

	void evolve_all();
	Cell& at(int x, int y);

	Cell* begin();
	Cell* end();
private:
	int height;
	int width;
	std::vector<Cell> board;

	int generation;
	int population;
};

#endif
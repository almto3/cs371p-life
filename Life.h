#ifndef Life_h
#define Life_h

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

class Cell;

class AbstractCell {
public:
	/*	Order for neighbors in the vector
	  									8 1 5
	  									4 X 2
	  									7 3 6
	*/
	virtual Cell evolve(std::vector<Cell> neighbors) = 0;
	virtual void print(std::ostream& out) = 0;
	virtual AbstractCell* clone() const = 0;

	AbstractCell(bool border = false) : is_border(border) {}

protected:
	bool alive;
	bool is_border;
};

class ConwayCell : public AbstractCell {
public:
	ConwayCell(const char& input);
	void print(std::ostream& out);
	Cell evolve(std::vector<Cell> neighbors);

	ConwayCell* clone() const;

private:
	FRIEND_TEST(ConwayFixture, conway_construct1);
	FRIEND_TEST(ConwayFixture, conway_construct2);
};

class FredkinCell : public AbstractCell {
public:
	FredkinCell(const char& input);
	FredkinCell(int age_, bool alive_);
	void print(std::ostream& out);
	Cell evolve(std::vector<Cell> neighbors);

	FredkinCell* clone() const;

private:
	int age;
	FRIEND_TEST(FredkinFixture, fredkin_construct1);
	FRIEND_TEST(FredkinFixture, fredkin_construct2);
	FRIEND_TEST(FredkinFixture, fredkin_construct3);
	FRIEND_TEST(FredkinFixture, fredkin_construct4);
	FRIEND_TEST(FredkinFixture, fredkin_construct5);
};

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
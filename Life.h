#ifndef Life_h
#define Life_h

#include <vector>
#include <iostream>

class AbstractCell {
	friend virtual ostream& operator<<(ostream& lhs, const AbstractCell& rhs);

public:
	virtual AbstractCell evolve(vector<AbstractCell *> neighbors);
protected:
	bool alive;
};

class ConwayCell : protected AbstractCell {
	friend ostream& operator<<(ostream& lhs, const ConwayCell& rhs);

public:
	ConwayCell(const char& input);
	ConwayCell evolve(vector<AbstractCell *> neighbors);
};

class FredkinCell : protected AbstractCell {
	friend ostream& operator<<(ostream& lhs, const FredkinCell& rhs);

public:
	FredkinCell(const char& input);
	FredkinCell evolve(vector<AbstractCell *> neighbors);
private:
	int age;
};

class Cell {
public:
	AbstractCell *cell;

	Cell(AbstractCell* c);
	Cell(Cell& c);
	~Cell();
	Cell& operator=(const Cell& rhs);
};

template <typename T>
class Life<T> {
	friend ostream& operator<<(ostream& lhs, const Life<T> rhs);

public:
	Life(istream& board);

	void evolve_all();
	Cell& at(int x, int y);

	Cell* begin();
	Cell* end();
private:
	int height;
	int width;
	vector<Cell> cells;

	int generation;
	int population;
};

#endif
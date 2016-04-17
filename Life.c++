#include <vector>
#include <iostream>

#include "Life.h"

using namespace std;

ConwayCell::ConwayCell(const char& input) {
	if (input == '*')
		alive = true;
	else
		alive = false;
}

ConwayCell* ConwayCell::clone() const {
	return new ConwayCell(*this);
}

Cell ConwayCell::evolve(vector<Cell> neighbors) {
	int live_neighbors = 0;

	for (Cell n : neighbors)
		if (n.acell->*(&ConwayCell::alive))
			live_neighbors++;

	if (alive) {
		if (live_neighbors < 2 || live_neighbors > 3)
			return Cell(new ConwayCell('.'));
		else
			return Cell(new ConwayCell('*'));
	} 
	else { // dead
		if (live_neighbors == 3)
			return Cell(new ConwayCell('*'));
		else
			return Cell(new ConwayCell('.'));
	}
}

void ConwayCell::print(ostream& out) {
	if (alive)
		out << '*';
	else
		out << '.';
}


/*FredkinCell* FredkinCell::clone() const {
	return new FredkinCell(*this);
}*/


Cell::Cell(const Cell& c) {
	acell = c.acell->clone();
}

Cell::~Cell() {
	delete acell;
}

Cell& Cell::operator=(const Cell& rhs) {
	acell = rhs.acell->clone();
	return *this;
}

#include <vector>
#include <iostream>
#include <cassert>

#include "Life.h"

using namespace std;

// ----------
// ConwayCell
// ----------

ConwayCell::ConwayCell(const char& input) {
	assert(input == '*' || input == '.');

	border = false;

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
		if (!(n.acell->*(&ConwayCell::border)) && n.acell->*(&ConwayCell::alive))
			live_neighbors++;

	if (alive) {
		if (live_neighbors < 2 || live_neighbors > 3)
			return Cell(new ConwayCell('.'));
		else
			return Cell(new ConwayCell('*'));
	} else { // dead
		if (live_neighbors == 3)
			return Cell(new ConwayCell('*'));
		else
			return Cell(new ConwayCell('.'));
	}
}

ostream& ConwayCell::print(ostream& out) const {
	if (alive)
		return out << '*';
	else
		return out << '.';
}

// -----------
// FredkinCell
// -----------

FredkinCell::FredkinCell(const char& input) : AbstractCell(false) {
	if (input == '-') {
		age = 0;
		alive = false;
	} else if (input >= '0' && input <= '9') {
		age = input - '0';
		alive = true;
	} else {
		age = 10;
		alive = true;
	}
}

FredkinCell::FredkinCell(int age_, bool alive_) : AbstractCell(false) {
	age = age_;
	alive = alive_;
}

FredkinCell* FredkinCell::clone() const {
	return new FredkinCell(*this);
}

Cell FredkinCell::evolve(vector<Cell> neighbors) {
	int live_neighbors = 0;

	for (int i = 0; i < 4; i++){
		Cell n = neighbors[i];
		if (!(n.acell->*(&FredkinCell::border)) && n.acell->*(&FredkinCell::alive))
			live_neighbors++;
	}

	if (alive) {
		if (live_neighbors == 0 || live_neighbors == 2 || live_neighbors == 4)
			return Cell(new FredkinCell(age, false));
		else {
			return Cell(new FredkinCell(age + 1, true));
		}
	} else { // dead
		if (live_neighbors == 3 || live_neighbors == 1)
			return Cell(new FredkinCell(age, true));
		else
			return Cell(new FredkinCell(age, false));
	}

}

ostream& FredkinCell::print(ostream& out) const {
	if (!alive)
		return out << '-';
	else {
		if (age < 10) 
			return out << age;
		else 
			return out << '+';
	}
}

// ----
// Cell
// ----

Cell::Cell(const Cell& c) {
	acell = c.acell->clone();
}

Cell::Cell(const char& c) {
	if (c == '.' || c == '*')
		acell = new ConwayCell(c);
	else
		acell = new FredkinCell(c);
}

/*Cell::~Cell() {
	delete acell;
}*/

Cell& Cell::operator=(const Cell& rhs) {
	acell = rhs.acell->clone();
	return *this;
}

/*Cell operator+(Cell& old_cell, vector<Cell> neighbors) {
	return old_cell.acell->evolve(neighbors);
}*/

ostream& operator<<(ostream& out, const Cell c) {
	return c.acell->print(out);
}

istream& operator>>(istream& in, Cell& c) {
	char input = in.get();

	c = Cell(input);

	return in;
}


// ----
// Life
// ----

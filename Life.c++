#include <vector>
#include <iostream>
#include <cassert>

#include "Life.h"

using namespace std;

// ------------
// AbstractCell
// ------------

ostream& operator<<(ostream& out, const AbstractCell& c) {
	return c.print(out);
}

istream& operator>>(istream& in, AbstractCell& c) {
	return in;
}

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

ConwayCell operator+(const ConwayCell& old_cell, const ConwayCell neighbors[8]) {
	int live_neighbors = 0;

	for (int i = 0; i < 8; i++)
		if (!neighbors[i].border && neighbors[i].alive)
			live_neighbors++;

	if (old_cell.is_alive()) {
		if (live_neighbors < 2 || live_neighbors > 3)
			return ConwayCell('.');
		else
			return ConwayCell('*');
	} else { // dead
		if (live_neighbors == 3)
			return ConwayCell('*');
		else
			return ConwayCell('.');
	}
}


ConwayCell* ConwayCell::clone() const {
	return new ConwayCell(*this);
}

Cell ConwayCell::evolve(const Cell neighbors[8]) const {
	int live_neighbors = 0;

	for (int i = 0; i < 8; i++) 
		if (!neighbors[i].is_border() && neighbors[i].is_alive())
			live_neighbors++;

	if (alive) {
		if (live_neighbors < 2 || live_neighbors > 3)
			return Cell(ConwayCell('.'));
		else
			return Cell(ConwayCell('*'));
	} else { // dead
		if (live_neighbors == 3)
			return Cell(ConwayCell('*'));
		else
			return Cell(ConwayCell('.'));
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
		age_ = 0;
		alive = false;
	} else if (input >= '0' && input <= '9') {
		age_ = input - '0';
		alive = true;
	} else {
		age_ = 10;
		alive = true;
	}
}

FredkinCell operator+(const FredkinCell& old_cell, const FredkinCell neighbors[8]) {
	int live_neighbors = 0;

	for (int i = 0; i < 4; i++)
		if (!neighbors[i].border && neighbors[i].alive)
			live_neighbors++;

	if (old_cell.is_alive()) {
		if (live_neighbors == 0 || live_neighbors == 2 || live_neighbors == 4)
			return FredkinCell(old_cell.age(), false);
		else {
			return FredkinCell(old_cell.age() + 1, true);
		}
	} else { // dead
		if (live_neighbors == 3 || live_neighbors == 1)
			return FredkinCell(old_cell.age(), true);
		else
			return FredkinCell(old_cell.age(), false);
	}
}

FredkinCell::FredkinCell(int a, bool alive_) : AbstractCell(false) {
	age_ = a;
	alive = alive_;
}

FredkinCell* FredkinCell::clone() const {
	return new FredkinCell(*this);
}

Cell FredkinCell::evolve(const Cell neighbors[8]) const {
	int live_neighbors = 0;

	for (int i = 0; i < 4; i++)
		if (!neighbors[i].is_border() && neighbors[i].is_alive())
			live_neighbors++;

	if (alive) {
		if (live_neighbors == 0 || live_neighbors == 2 || live_neighbors == 4)
			return Cell(FredkinCell(age_, false));
		else {
			return Cell(FredkinCell(age_ + 1, true));
		}
	} else { // dead
		if (live_neighbors == 3 || live_neighbors == 1)
			return Cell(FredkinCell(age_, true));
		else
			return Cell(FredkinCell(age_, false));
	}
}

ostream& FredkinCell::print(ostream& out) const {
	if (!alive)
		return out << '-';
	else {
		if (age_ < 10) 
			return out << age_;
		else 
			return out << '+';
	}
}

const int FredkinCell::age() const {
	return age_;
}

// ----
// Cell
// ----


Cell::Cell(const char& c) {
	if (c == '.' || c == '*')
		this->acell = new ConwayCell(c);
	else
		this->acell = new FredkinCell(c);
}

Cell::Cell(const Cell& c) {
	this->acell = c.acell->clone();
}

Cell::~Cell() {
	delete acell;
}

Cell& Cell::operator=(const Cell& rhs) {
	acell = rhs.acell->clone();
	return *this;
}

Cell operator+(const Cell& old_cell, const Cell neighbors[8]) {
	Cell new_cell = old_cell.acell->evolve(neighbors);

	// If Life is instantiated with Cell, then when a FredkinCell's age is to become 2, and only then, it becomes a live ConwayCell instead.
	FredkinCell *oc;
	if ((oc = dynamic_cast<FredkinCell *>(old_cell.acell)) != nullptr)
		if (oc->age() == 1 && (static_cast<FredkinCell *>(new_cell.acell))->age() == 2)
			return Cell(ConwayCell('*'));

	return new_cell;
}

ostream& operator<<(ostream& out, const Cell c) {
	return c.acell->print(out);
}

istream& operator>>(istream& in, Cell& c) {
	char input = in.get();

	c = Cell(input);

	return in;
}

bool Cell::is_alive() const {
	return acell->is_alive();
}

bool Cell::is_border() const {
	return acell->is_border();
}

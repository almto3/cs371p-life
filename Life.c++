#include <vector>
#include <iostream>

#include "Life.h"

using namespace std;

/*
*
	ConwayCell
*
*/

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
		if (!(n.acell->*(&ConwayCell::is_border)) && n.acell->*(&ConwayCell::alive))
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

void ConwayCell::print(ostream& out) {
	if (alive)
		out << '*';
	else
		out << '.';
}

/*
*
	FREDKIN
*
*/


FredkinCell::FredkinCell(const char& input) {
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

FredkinCell::FredkinCell(int age_, bool alive_) {
	age = age_;
	alive = alive_;
}

FredkinCell* FredkinCell::clone() const {
	return new FredkinCell(*this);
}

Cell FredkinCell::evolve(vector<Cell> neighbors) {
	int live_neighbors = 0;

	for (int i = 0; i< 4; i++){
		Cell n = neighbors[i];
		if (!(n.acell->*(&FredkinCell::is_border)) && n.acell->*(&FredkinCell::alive))
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

void FredkinCell::print(ostream& out) {
	if (!alive)
		out << '-';
	else {
		if (age < 10) 
			out << age;
		else 
			out << '+';
	}
}

/*
*
	Cell
*
*/

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


// ----
// Life
// ----

template <class T>
Life<T>::Life(istream& in) {
	bool last_char_was_newline = true; // Used to determine where the input ends and where to add borders

	width = 0;
	height = 0;

	vector<Cell> temp_board; // Using this because we need to add the top border after we're done

	while (true) {
		char input;
		in >> input;

		if (input == '\n') {
			++height;

			if (last_char_was_newline)
				break;
			else {
				last_char_was_newline = true;

				// Add border on right side
				temp_board.push_back(Cell(new T(true)));

				continue;
			}
		}

		if (height < 1)
			++width;

		if (last_char_was_newline == true) { // Add border on left side
			temp_board.push_back(Cell(new T(true)));
		}

		T* new_cell = new T(input);
		temp_board.push_back(Cell(new_cell));

		last_char_was_newline = false;
	}

	// Add border for last row
	for (int i = 0; i < width + 2; i++)
		temp_board.push_back(Cell(new T(true)));

	// Add border for first row
	for (int i = 0; i < width + 2; i++)
		board.push_back(Cell(new T(true)));

	// Put the rest of the board after the top border
	board.insert(board.end(), temp_board.begin(), temp_board.end());
}

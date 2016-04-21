#ifndef Life_h
#define Life_h

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

class Cell;

// 	------------------------------------------------------------------
//	Class AbstractCell is the base class to FredkinCell and ConwayCell
//	------------------------------------------------------------------
class AbstractCell {
	
	/**
	 * print a cell's symbol
	 * @param out the ostream to write to
	 * @param c the cell we want to print
	 * @return the ostream
	 */
	friend std::ostream& operator<<(std::ostream& out, const AbstractCell& c);

	/**
	 * read a symbol to a cell
	 * @param in the istream to read from
	 * @param c the cell we want to print
	 * @return the ostream
	 */
	friend std::istream& operator>>(std::istream& in, AbstractCell& c);

protected:
	bool alive;		//boolean that holds the state of the cell
	bool border;	//boolean that tells if the cell is a border or not
public:

	/*	Order for neighbors in the vector
	 *  									8 1 5
	 *  									4 C 2
	 *  									7 3 6
	 */

	/**
	 * evolve the cell
	 * @param neighbors the neighbors to the calling cell
	 * @return the evolved cell
	 */
	virtual Cell evolve(std::vector<Cell> neighbors) const = 0;

	/**
	 * print this cell's symbol
	 * @param out the ostream to write to
	 * @return the ostream
	 */
	virtual std::ostream& print(std::ostream& out) const = 0;

	/**
	 * clone this cell
	 * @return a pointer to a clone of the cell
	 */
	virtual AbstractCell* clone() const = 0;

	/**
	 * destructor
	 */
	virtual ~AbstractCell() {}

	/**
	 * constructor
	 * @param border_ the value if the cell is a border or not
	 */
	AbstractCell(bool border_ = false) : border(border_) {}

	/**
	 * is the cell alive or dead?
	 * @return true if alive, false if dead
	 */
	virtual const bool is_alive() const { return alive; }

	/**
	 * is the cell a border?
	 * @return true if border, false if not a border
	 */
	virtual const bool is_border() const { return border; }
};

// 	---------------------------------------------------
//	Class ConwayCell is the class to handle conwaycells 
//	---------------------------------------------------
class ConwayCell : public AbstractCell {

	/**
	 * evolve this cell, the operator is to be called on the cell and it's neighbors 
	 * @param old_cell the cell to evolve
	 * @param neighbors a vector of neighbors, in the order up, right, down, left, up-right, down-right, down-left, up-left
	 * @return a new cell that's evolved from old_cell and neighbors
	 */
	friend ConwayCell operator+(ConwayCell old_cell, const std::vector<ConwayCell> neighbors);

public:

	/**
	 * constructor
	 * @param border_ the value if the cell is a border or not
	 */
	ConwayCell(bool border_ = false) : AbstractCell(border_) {}

	/**
	 * constructor
	 * @param input the character representation of a cell
	 */
	ConwayCell(const char& input);

	/**
	 * print this cell's symbol
	 * @param out the ostream to write to
	 * @return the ostream
	 */
	std::ostream& print(std::ostream& out) const;

	/**
	 * evolve the cell
	 * @param neighbors the neighbors to the calling cell
	 * @return the evolved cell
	 */
	Cell evolve(std::vector<Cell> neighbors) const;

	/**
	 * preforms a deep copy on the cell
	 * @return a pointer to the new cell
	 */
	ConwayCell* clone() const;
};

// 	-----------------------------------------------------
//	Class FredkinCell is the class to handle fredkincells 
//	-----------------------------------------------------
class FredkinCell : public AbstractCell {

	/**
	 * evolve this cell, the operator is to be called on the cell and it's neighbors
	 * @param old_cell the cell to evolve
	 * @param neighbors a vector of neighbors, in the order up, right, down, left, up-right, down-right, down-left, up-left
	 * @return a new cell that's evolved from old_cell and neighbors
	 */
	friend FredkinCell operator+(FredkinCell old_cell, const std::vector<FredkinCell> neighbors);

public:

	/**
	 * constructor
	 * @param border_ the value if the cell is a border or not
	 */
	FredkinCell(bool border_ = false) : AbstractCell(border_) {}

	/**
	 * constructor
	 * @param input the character representation of a cell
	 */
	FredkinCell(const char& input);

	/**
	 * constructor
	 * @param age_ the age of the cell 
	 * @param alive_ the boolean to determine is the cell is alive or not
	 */
	FredkinCell(int age_, bool alive_);

	/**
	 * print this cell's symbol
	 * @param out the ostream to write to
	 * @return the ostream
	 */
	std::ostream& print(std::ostream& out) const;

	/**
	 * evolve the cell
	 * @param neighbors the neighbors to the calling cell
	 * @return the evolved cell
	 */
	Cell evolve(std::vector<Cell> neighbors) const;

	/**
	 * preforms a deep copy on the cell
	 * @return a pointer to the new cell
	 */
	FredkinCell* clone() const;

	/**
	 * what is the age of the fredkincell?
	 * @return the age of the fredkincell
	 */
	const int age() const;

protected:
	int age_;	//int that hold the age of the cell
};

// 	-----------------------------------------------------------------------
//	Class Cell is the handler class for handle fredkincells and conwaycells
//	-----------------------------------------------------------------------
class Cell {

	/**
	 * evolve this cell, the operator is to be called on the cell and it's neighbors, works for all cells
	 * @param old_cell the cell to evolve
	 * @param neighbors a vector of neighbors, in the order up, right, down, left, up-right, down-right, down-left, up-left
	 * @return a new cell that's evolved from old_cell and neighbors
	 */
	friend Cell operator+(Cell old_cell, const std::vector<Cell> neigbors);

	/**
	 * print this cell's symbol, works for all cells
	 * @param out the ostream to write to
	 * @return the ostream
	 */
	friend std::ostream& operator<<(std::ostream& out, const Cell c);

	/**
	 * read a symbol to a cell, works for all cells
	 * @param in the istream to read from
	 * @param c the cell we want to print
	 * @return the ostream
	 */
	friend std::istream& operator>>(std::istream& in, Cell& c);

public:
	AbstractCell *acell;		//pointer to the cell object encapsulated by the Cell class

	/**
	 * constructor
	 * @param c the cell to be encapsulated, assigned to variable acell
	 */
	Cell(AbstractCell* c = nullptr) : acell(c) {}

	/**
	 * constructor
	 * @param const c the cell to be encapsulated, assigned to variable acell
	 */
	Cell(const AbstractCell& c) : acell(c.clone()) {}

	/**
	 * constructor
	 * @param border_ the value if the cell is a border or not
	 */
	Cell(bool border_) : acell(new ConwayCell(border_)) {}

	/**
	 * constructor
	 * @param input the character representation of a cell
	 */
	Cell(const char& c);

	/**
	 * copy constructor
	 * @param c is the cell to be copied to this cell
	 */
	Cell(const Cell& c);

	/**
	 * destructor
	 */
	~Cell();

	/**
	 * will call clone on this cell with the parameter rhs
	 * @param rhs the right hand side side to be copied from
	 * @return a pointer this
	 */
	Cell& operator=(const Cell& rhs);

	/**
	 * is the cell alive or dead?
	 * @return true if alive, false if dead
	 */
	bool is_alive() const;
};

// 	----------------------------------------------------
//	Generic Class Life has the board to the game of life
//	----------------------------------------------------
template <class T>
class Life {
public:

	/**
	 * constructor
	 * @param in the istream to read from
	 * @param h is the height of the board (without borders as they are hidden from the user)
	 * @param w is the width of the board (without borders as they are hidden from the user)
	 */	
	Life(std::istream& in, int h, int w) {
		width = w;
		height = h;
		generation = 0;
		population = 0;

		int x = 0;
		int y = 0;

		board.resize((width + 2) * (height + 2), T(true)); // initialize board, fill it with borders

		while (true) {
			int input = in.get();

			if (input == EOF || (input == '\n' && y == 0))
				break;

			if (input == '\n') {
				x++;
				assert(y == width);
				y = 0;
				continue;
			}

			// Add the actual cell
			T new_cell = T((char) input);

			if (new_cell.is_alive())
				population++;

			at(x, y).~T();	// deallocate
			at(x, y) = new_cell;

			y++;
		}

		assert(x == height);
	}

	/**
	 * print this cell's symbol, works for all cells
	 * @param out the ostream to write to
	 */
	void print(std::ostream& out) {
		out << "Generation = " << generation << ", Population = " << population << "." << std::endl;
		for (int x = 1; x < height + 1; x++) {
			for (int y = 1; y < width + 1; y++) {
				T c = board[x * (width + 2) + y];
				out << c;
			}
			out << std::endl;
		}
		out << std::endl;
	}

	/**
	 * will call the function evolve on the whole cell
	 */
	void evolve_all() {
		population = 0;

		std::vector<T> temp_board = board;

		for (int x = 0; x < height; x++) {
			for (int y = 0; y < width; y++) {
				T cell = at(x, y);
				std::vector<T> neighbors;

				//getting the neighbors, in case of fredkincell, evolve will only consider the first four entries
				neighbors.push_back(temp_board.at((x + 1) * (width + 2) + y));		// up
				neighbors.push_back(temp_board.at((x + 2) * (width + 2) + y + 1));	// right
				neighbors.push_back(temp_board.at((x + 1) * (width + 2) + y + 2));	// down
				neighbors.push_back(temp_board.at((x) * (width + 2) + y + 1));		// left
				neighbors.push_back(temp_board.at((x + 2) * (width + 2) + y));		// top-right
				neighbors.push_back(temp_board.at((x + 2) * (width + 2) + y + 2));	// bottom-right
				neighbors.push_back(temp_board.at((x) * (width + 2) + y + 2));		// bottom-left
				neighbors.push_back(temp_board.at((x) * (width + 2) + y));			// top-left

				T new_cell = cell + neighbors;
				
				if (new_cell.is_alive())
					population++;
				
				at(x, y).~T();		// deallocate old cell to avoid memory leaks
				at(x, y) = new_cell;
			}
		}

		generation++;
	}

	/**
	 * will retrieve the cell at position (x, y) in the board
	 * @param x the horizontal variable (without borders as they are hidden from the user)
	 * @param y the vertical variable (without borders as they are hidden from the user)
	 * @return the cell at position (x,y)
	 */	
	T& at(int x, int y) {
		return board.at((x + 1) * (width + 2) + y + 1);
	}

	/**
	 * const version of at(), will retrieve the cell at position (x, y) in the board
	 * @param x the horizontal variable (without borders as they are hidden from the user)
	 * @param y the vertical variable (without borders as they are hidden from the user)
	 * @return the cell at position (x,y)
	 */	
	const T& at(int x, int y) const {
		return board.at((x + 1) * (width + 2) + y + 1);
	}

	// 	-------------------------------------------------
	//	Nested Class iterator, it will iterate over board
	//	-------------------------------------------------
	template <class T2>
	class iterator {
	public:

		/**
		 * constructor
	 	 * @param l is the life instance to iterate over
	 	 * @param x the horizontal variable (without borders as they are hidden from the user)
	 	 * @param y the vertical variable (without borders as they are hidden from the user)
		 */	
		iterator(Life& l, int x_, int y_) : life(l), x(x_), y(y_) {}

		/**
		 * operator * will override the * operator for iterator
	 	 * @return a reference to the cell this iterator points to
		 */	
		T2& operator*() const {
			return life.at(x, y);
		}
		iterator<T2>& operator++() {
			y++;
			if (y >= life.width) {
				x++;
				y = 0;
			}
			return *this;
		}
		iterator<T2>& operator--() {
			y--;
			if (y < 0) {
				x--;
				y = life.width - 1;
			}
			return *this;
		}
		bool operator==(const iterator<T2>& rhs) const {
			return x == rhs.x && y == rhs.y && &life == &rhs.life;
		}
		bool operator!=(const iterator<T2>& rhs) const {
			return !(*this == rhs);
		}
	private:
		Life<T2>& life;
		int x;
		int y;
	};

	template <class T2>
	class const_iterator {
	public:
		const_iterator(const Life& l, int x_, int y_) : life(l), x(x_), y(y_) {}

		const T2& operator*() const {
			return life.at(x, y);
		}
		const_iterator<T2>& operator++() {
			y++;
			if (y >= life.width) {
				x++;
				y = 0;
			}
			return *this;
		}
		const_iterator<T2>& operator--() {
			y--;
			if (y < 0) {
				x--;
				y = life.width - 1;
			}
			return *this;
		}
		bool operator==(const const_iterator<T2>& rhs) const {
			return x == rhs.x && y == rhs.y && &life == &rhs.life;
		}
		bool operator!=(const const_iterator<T2>& rhs) const {
			return !(*this == rhs);
		}
	private:
		const Life<T2>& life;
		int x;
		int y;
	};

	iterator<T> begin() {
		return iterator<T>(*this, 0, 0);
	}
	const_iterator<T> begin() const {
		return const_iterator<T>(*this, 0, 0);
	}
	iterator<T> end() {
		return iterator<T>(*this, height - 1, width);
	}
	const_iterator<T> end() const {
		return const_iterator<T>(*this, height - 1, width);
	}
private:
	int height;
	int width;
	std::vector<T> board;

	int generation;
	int population;

	FRIEND_TEST(LifeFixture, life_construct1);
	FRIEND_TEST(LifeFixture, life_construct2);
	FRIEND_TEST(LifeFixture, life_construct3);
};

#endif
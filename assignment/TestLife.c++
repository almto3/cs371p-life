#include <sstream>
#include <vector>

#include "gtest/gtest.h"

#include "Life.h"

using namespace std;

TEST(ConwayFixture, conway_construct1) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.is_alive(), true);
	ASSERT_EQ(c.is_border(), false);
}

TEST(ConwayFixture, conway_construct2) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.is_alive(), false);
	ASSERT_EQ(c.is_border(), false);
}

TEST(ConwayFixture, conway_construct_border) {
	ConwayCell b = ConwayCell(true);
	ASSERT_EQ(b.is_border(), true);
}


TEST(ConwayFixture, conway_output1) {
	ConwayCell c = ConwayCell('*');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "*");
}

TEST(ConwayFixture, conway_output2) {
	ConwayCell c = ConwayCell('.');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), ".");
}


TEST(ConwayFixture, conway_clone1) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.is_alive(), true);

	ConwayCell* c2 = c.clone();
	c = ConwayCell('.');
	ASSERT_EQ(c2->is_alive(), true);

	delete c2;
}

TEST(ConwayFixture, conway_clone2) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.is_alive(), false);

	ConwayCell* c2 = c.clone();
	c = ConwayCell('*');
	ASSERT_EQ(c2->is_alive(), false);

	delete c2;
}


class ConwayEvolutionFixture : public ::testing::TestWithParam<vector<char>> {
	// Fixture for running tests of evolution. The argument is a vector containing the neighbors, then the value of the cell, then the expected value
};

TEST_P(ConwayEvolutionFixture, conway_evolve) {
	vector<char> param = GetParam();

	char expected = param.back();
	param.pop_back();
	char cell_value = param.back();
	param.pop_back();

	Cell neighbors[8];
	int i = 0;
	for (char c : param) {
		neighbors[i++] = Cell(ConwayCell(c));
	}

	ConwayCell c = ConwayCell(cell_value);
	Cell c2 = c.evolve(neighbors);

	ostringstream s;
	s << c2;
	ASSERT_EQ(s.str()[0], expected);
}

TEST_P(ConwayEvolutionFixture, conway_evolve_plus) {
	vector<char> param = GetParam();

	char expected = param.back();
	param.pop_back();
	char cell_value = param.back();
	param.pop_back();

	ConwayCell neighbors[8];
	int i = 0;
	for (char c : param) {
		neighbors[i++] = ConwayCell(c);
	}

	ConwayCell c = ConwayCell(cell_value);
	ConwayCell c2 = c + neighbors;

	ostringstream s;
	s << c2;
	ASSERT_EQ(s.str()[0], expected);
}

INSTANTIATE_TEST_CASE_P(ConwayEvolutionAlive, ConwayEvolutionFixture, ::testing::Values(
	vector<char>({'.', '.', '.', '.', '.', '.', '.', '.',   '*', '.'}),
	vector<char>({'*', '.', '.', '.', '.', '.', '.', '.',   '*', '.'}),
	vector<char>({'*', '*', '.', '.', '.', '.', '.', '.',   '*', '*'}),
	vector<char>({'*', '*', '*', '.', '.', '.', '.', '.',   '*', '*'}),
	vector<char>({'*', '*', '*', '*', '.', '.', '.', '.',   '*', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '.', '.', '.',   '*', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '.', '.',   '*', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '*', '.',   '*', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '*', '*',   '*', '.'})
	));

INSTANTIATE_TEST_CASE_P(ConwayEvolutionDead, ConwayEvolutionFixture, ::testing::Values(
	vector<char>({'.', '.', '.', '.', '.', '.', '.', '.',   '.', '.'}),
	vector<char>({'*', '.', '.', '.', '.', '.', '.', '.',   '.', '.'}),
	vector<char>({'*', '*', '.', '.', '.', '.', '.', '.',   '.', '.'}),
	vector<char>({'*', '*', '*', '.', '.', '.', '.', '.',   '.', '*'}),
	vector<char>({'*', '*', '*', '*', '.', '.', '.', '.',   '.', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '.', '.', '.',   '.', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '.', '.',   '.', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '*', '.',   '.', '.'}),
	vector<char>({'*', '*', '*', '*', '*', '*', '*', '*',   '.', '.'})
	));





TEST(FredkinFixture, fredkin_construct1) {
	FredkinCell f = FredkinCell('-');
	ASSERT_EQ(f.is_alive(), false);
	ASSERT_EQ(f.is_border(), false);
	ASSERT_EQ(f.age(), 0);
}

TEST(FredkinFixture, fredkin_construct2) {
	FredkinCell f = FredkinCell('0');
	ASSERT_EQ(f.is_alive(), true);
	ASSERT_EQ(f.is_border(), false);
	ASSERT_EQ(f.age(), 0);
}

TEST(FredkinFixture, fredkin_construct3) {
	FredkinCell f = FredkinCell('5');
	ASSERT_EQ(f.is_alive(), true);
	ASSERT_EQ(f.is_border(), false);
	ASSERT_EQ(f.age(), 5);
}

TEST(FredkinFixture, fredkin_construct4) {
	FredkinCell f = FredkinCell('9');
	ASSERT_EQ(f.is_alive(), true);
	ASSERT_EQ(f.is_border(), false);
	ASSERT_EQ(f.age(), 9);
}

TEST(FredkinFixture, fredkin_construct5) {
	FredkinCell f = FredkinCell('+');
	ASSERT_EQ(f.is_alive(), true);
	ASSERT_EQ(f.is_border(), false);
	ASSERT_GE(f.age(), 10);
}

TEST(FredkinFixture, fredkin_output1) {
	FredkinCell c = FredkinCell('-');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "-");
}

TEST(FredkinFixture, fredkin_output2) {
	FredkinCell c = FredkinCell('0');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "0");
}

TEST(FredkinFixture, fredkin_output3) {
	FredkinCell c = FredkinCell('3');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "3");
}

TEST(FredkinFixture, fredkin_output4) {
	FredkinCell c = FredkinCell('9');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "9");
}

TEST(FredkinFixture, fredkin_output5) {
	FredkinCell c = FredkinCell('+');

	ostringstream s;
	c.print(s);
	ASSERT_EQ(s.str(), "+");
}

class FredkinEvolutionFixture : public ::testing::TestWithParam<vector<char>> {
	// Fixture for running tests of evolution. The argument is a vector containing the neighbors, then the value of the cell, then the expected value
};

TEST_P(FredkinEvolutionFixture, fredkin_evolve) {
	vector<char> param = GetParam();

	char expected = param.back();
	param.pop_back();
	char cell_value = param.back();
	param.pop_back();

	Cell neighbors[8];
	int i = 0;
	for (char c : param) {
		neighbors[i++] = Cell(new FredkinCell(c));
	}

	FredkinCell c = FredkinCell(cell_value);
	Cell c2 = c.evolve(neighbors);

	ostringstream s;
	s << c2;
	ASSERT_EQ(s.str()[0], expected);
}

TEST_P(FredkinEvolutionFixture, fredkin_evolve_plus) {
	vector<char> param = GetParam();

	char expected = param.back();
	param.pop_back();
	char cell_value = param.back();
	param.pop_back();

	FredkinCell neighbors[8];
	int i = 0;
	for (char c : param) {
		neighbors[i++] = FredkinCell(c);
	}

	FredkinCell c = FredkinCell(cell_value);
	FredkinCell c2 = c + neighbors;

	ostringstream s;
	s << c2;
	ASSERT_EQ(s.str()[0], expected);
}


INSTANTIATE_TEST_CASE_P(FredkinEvolutionAlive, FredkinEvolutionFixture, ::testing::Values(
	vector<char>({'-', '-', '-', '-', '-', '-', '-', '-',   '0', '-'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '0', '1'}),
	vector<char>({'2', '2', '-', '-', '-', '-', '-', '-',   '0', '-'}),
	vector<char>({'2', '2', '2', '-', '-', '-', '-', '-',   '0', '1'}),
	vector<char>({'2', '2', '2', '2', '-', '-', '-', '-',   '0', '-'}),

	vector<char>({'-', '-', '-', '-', '2', '-', '4', '-',   '0', '-'}),
	vector<char>({'6', '-', '-', '-', '-', '5', '-', '-',   '0', '1'}),
	vector<char>({'2', '5', '-', '-', '3', '-', '-', '1',   '0', '-'}),
	vector<char>({'2', '8', '2', '-', '0', '-', '5', '-',   '0', '1'}),
	vector<char>({'1', '2', '+', '2', '3', '4', '-', '-',   '0', '-'})
	));

INSTANTIATE_TEST_CASE_P(FredkinEvolutionDead, FredkinEvolutionFixture, ::testing::Values(
	vector<char>({'-', '-', '-', '-', '-', '-', '-', '-',   '-', '-'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '-', '0'}),
	vector<char>({'2', '2', '-', '-', '-', '-', '-', '-',   '-', '-'}),
	vector<char>({'2', '2', '2', '-', '-', '-', '-', '-',   '-', '0'}),
	vector<char>({'2', '2', '2', '2', '-', '-', '-', '-',   '-', '-'}),

	vector<char>({'-', '-', '-', '-', '2', '-', '4', '-',   '-', '-'}),
	vector<char>({'6', '-', '-', '-', '-', '5', '-', '-',   '-', '0'}),
	vector<char>({'2', '5', '-', '-', '3', '-', '-', '1',   '-', '-'}),
	vector<char>({'2', '8', '2', '-', '0', '-', '5', '-',   '-', '0'}),
	vector<char>({'1', '2', '+', '2', '3', '4', '-', '-',   '-', '-'})
	));

INSTANTIATE_TEST_CASE_P(FredkinEvolutionAlive2, FredkinEvolutionFixture, ::testing::Values(
	vector<char>({'-', '-', '-', '-', '-', '-', '-', '-',   '5', '-'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '1', '2'}),
	vector<char>({'2', '2', '-', '-', '-', '-', '-', '-',   '8', '-'}),
	vector<char>({'2', '2', '2', '-', '-', '-', '-', '-',   '9', '+'}),
	vector<char>({'2', '2', '2', '2', '-', '-', '-', '-',   '4', '-'}),

	vector<char>({'-', '-', '-', '-', '2', '-', '4', '-',   '5', '-'}),
	vector<char>({'6', '-', '-', '-', '-', '5', '-', '-',   '+', '+'}),
	vector<char>({'2', '5', '-', '-', '3', '-', '-', '1',   '1', '-'}),
	vector<char>({'2', '8', '2', '-', '0', '-', '5', '-',   '5', '6'}),
	vector<char>({'1', '2', '+', '2', '3', '4', '-', '-',   '0', '-'})
	));

// TODO: test when FredkinCells and ConwayCells border each other

// -----------
// CellFixture
// -----------

TEST(CellFixture, cell_conway_copy_constructor1) {
	ConwayCell cc = ConwayCell('*');
	ASSERT_EQ(cc.is_alive(), true);

	Cell c = Cell(&cc);
	ASSERT_EQ(c.acell->is_alive(), true);

	Cell c2 = c;
	c.acell = new ConwayCell('.');
	ASSERT_EQ(c2.acell->is_alive(), true);
}

TEST(CellFixture, cell_conway_copy_constructor2) {
	ConwayCell cc = ConwayCell('.');
	ASSERT_EQ(cc.is_alive(), false);

	Cell c = Cell(&cc);
	ASSERT_EQ(c.acell->is_alive(), false);

	Cell c2 = c;
	c.acell = new ConwayCell('*');
	ASSERT_EQ(c2.acell->is_alive(), false);
}

TEST(CellFixture, cell_conway_copy_assignment1) {
	ConwayCell cc = ConwayCell('*');
	ASSERT_EQ(cc.is_alive(), true);

	ConwayCell cc2 = ConwayCell('.');
	ASSERT_EQ(cc2.is_alive(), false);

	Cell c = Cell(&cc);
	ASSERT_EQ(c.acell->is_alive(), true);

	Cell c2 = Cell(&cc2);
	ASSERT_EQ(c2.acell->is_alive(), false);

	c2 = c;
	c.acell = new ConwayCell('.');
	ASSERT_EQ(c2.acell->is_alive(), true);
}

TEST(CellFixture, cell_conway_copy_assignment2) {
	ConwayCell cc = ConwayCell('.');
	ASSERT_EQ(cc.is_alive(), false);

	ConwayCell cc2 = ConwayCell('*');
	ASSERT_EQ(cc2.is_alive(), true);

	Cell c = Cell(&cc);
	ASSERT_EQ(c.acell->is_alive(), false);

	Cell c2 = Cell(&cc2);
	ASSERT_EQ(c2.acell->is_alive(), true);

	c2 = c;
	c.acell = new ConwayCell('*');
	ASSERT_EQ(c2.acell->is_alive(), false);
}


class CellEvolutionFixture : public ::testing::TestWithParam<vector<char>> {
	// Fixture for running tests of evolution. The argument is a vector containing the neighbors, then the value of the cell, then the expected value

	
};

TEST_P(CellEvolutionFixture, cell_evolve) {
	vector<char> param = GetParam();

	char expected = param.back();
	param.pop_back();
	char cell_value = param.back();
	param.pop_back();

	Cell neighbors[8];
	int i = 0;
	for (char c : param) {
		neighbors[i++] = Cell(c);
	}

	Cell c = Cell(cell_value);
	Cell c2 = c + neighbors;

	ostringstream s;
	s << c2;
	ASSERT_EQ(s.str()[0], expected);
}

INSTANTIATE_TEST_CASE_P(CellEvolution, CellEvolutionFixture, ::testing::Values(

	//Dead Conway
	vector<char>({'.', '.', '-', '-', '.', '-', '.', '-',   '.', '.'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '.', '.'}),
	vector<char>({'*', '1', '-', '-', '.', '.', '-', '-',   '.', '.'}),
	vector<char>({'1', '*', '2', '-', '-', '-', '.', '-',   '.', '*'}),
	vector<char>({'3', '*', '1', '*', '.', '-', '.', '-',   '.', '.'}),
	vector<char>({'1', '*', '6', '+', '2', '.', '.', '.',   '.', '.'}),
	vector<char>({'6', '*', '9', '*', '+', '5', '-', '.',   '.', '.'}),
	vector<char>({'1', '*', '4', '*', '2', '4', '1', '-',   '.', '.'}),
	vector<char>({'*', '8', '2', '*', '0', '*', '5', '6',   '.', '.'}),

	//Alive Conway
	vector<char>({'.', '.', '-', '-', '.', '-', '.', '-',   '*', '.'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '*', '.'}),
	vector<char>({'*', '1', '-', '-', '.', '.', '-', '-',   '*', '*'}),
	vector<char>({'1', '*', '2', '-', '-', '-', '.', '-',   '*', '*'}),
	vector<char>({'3', '*', '1', '*', '.', '-', '.', '-',   '*', '.'}),
	vector<char>({'1', '*', '6', '+', '2', '.', '.', '.',   '*', '.'}),
	vector<char>({'6', '*', '9', '*', '+', '5', '-', '.',   '*', '.'}),
	vector<char>({'1', '*', '4', '*', '2', '4', '1', '-',   '*', '.'}),
	vector<char>({'*', '8', '2', '*', '0', '*', '5', '6',   '*', '.'}),

	//Dead Fredkin
	vector<char>({'.', '.', '-', '-', '.', '-', '.', '-',   '-', '-'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '-', '0'}),
	vector<char>({'*', '1', '-', '-', '.', '.', '-', '-',   '-', '-'}),
	vector<char>({'1', '*', '2', '-', '-', '-', '.', '-',   '-', '0'}),
	vector<char>({'3', '*', '1', '*', '.', '-', '.', '-',   '-', '-'}),
	vector<char>({'1', '*', '6', '+', '2', '.', '.', '.',   '-', '-'}),
	vector<char>({'6', '*', '9', '*', '+', '5', '-', '.',   '-', '-'}),
	vector<char>({'1', '*', '4', '*', '2', '4', '1', '-',   '-', '-'}),
	vector<char>({'*', '8', '2', '*', '0', '*', '5', '6',   '-', '-'}),

	//Alive Fredkin
	vector<char>({'.', '.', '-', '-', '.', '-', '.', '-',   '1', '-'}),
	vector<char>({'.', '.', '-', '-', '.', '-', '.', '-',   '2', '-'}),
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '1', '*'}),
	vector<char>({'*', '1', '-', '-', '.', '.', '-', '-',   '3', '-'}),
	vector<char>({'1', '*', '2', '-', '-', '-', '.', '-',   '4', '5'}),
	vector<char>({'3', '*', '1', '*', '.', '-', '.', '-',   '5', '-'}),
	vector<char>({'1', '*', '6', '+', '2', '.', '.', '.',   '6', '-'}),
	vector<char>({'6', '*', '9', '*', '+', '5', '-', '.',   '7', '-'}),
	vector<char>({'1', '*', '4', '*', '2', '4', '1', '-',   '8', '-'}),
	vector<char>({'*', '8', '2', '*', '0', '*', '5', '6',   '9', '-'})

	));

// --------
// LifeTest
// --------

TEST(LifeFixture, life_construct1) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in, 4, 3);

	EXPECT_EQ(l.width, 3);
	EXPECT_EQ(l.height, 4);
	EXPECT_EQ(l.board.size(), (l.width + 2) * (l.height + 2));

	EXPECT_EQ(l.board[0].is_border(), true);
	EXPECT_EQ(l.board[1].is_border(), true);
	EXPECT_EQ(l.board[2].is_border(), true);
	EXPECT_EQ(l.board[3].is_border(), true);
	EXPECT_EQ(l.board[4].is_border(), true);

	EXPECT_EQ(l.board[5].is_border(), true);
	EXPECT_EQ(l.board[6].is_border(), false); EXPECT_EQ(l.board[6].is_alive(), false);
	EXPECT_EQ(l.board[7].is_border(), false); EXPECT_EQ(l.board[7].is_alive(), false);
	EXPECT_EQ(l.board[8].is_border(), false); EXPECT_EQ(l.board[8].is_alive(), false);
	EXPECT_EQ(l.board[9].is_border(), true);

	EXPECT_EQ(l.board[10].is_border(), true);
	EXPECT_EQ(l.board[11].is_border(), false); EXPECT_EQ(l.board[11].is_alive(), false);
	EXPECT_EQ(l.board[12].is_border(), false); EXPECT_EQ(l.board[12].is_alive(), true);
	EXPECT_EQ(l.board[13].is_border(), false); EXPECT_EQ(l.board[13].is_alive(), false);
	EXPECT_EQ(l.board[14].is_border(), true);

	EXPECT_EQ(l.board[15].is_border(), true);
	EXPECT_EQ(l.board[16].is_border(), false); EXPECT_EQ(l.board[16].is_alive(), false);
	EXPECT_EQ(l.board[17].is_border(), false); EXPECT_EQ(l.board[17].is_alive(), false);
	EXPECT_EQ(l.board[18].is_border(), false); EXPECT_EQ(l.board[18].is_alive(), false);
	EXPECT_EQ(l.board[19].is_border(), true);

	EXPECT_EQ(l.board[20].is_border(), true);
	EXPECT_EQ(l.board[21].is_border(), false); EXPECT_EQ(l.board[21].is_alive(), true);
	EXPECT_EQ(l.board[22].is_border(), false); EXPECT_EQ(l.board[22].is_alive(), false);
	EXPECT_EQ(l.board[23].is_border(), false); EXPECT_EQ(l.board[23].is_alive(), false);
	EXPECT_EQ(l.board[24].is_border(), true);

	EXPECT_EQ(l.board[25].is_border(), true);
	EXPECT_EQ(l.board[26].is_border(), true);
	EXPECT_EQ(l.board[27].is_border(), true);
	EXPECT_EQ(l.board[28].is_border(), true);
	EXPECT_EQ(l.board[29].is_border(), true);
}

TEST(LifeFixture, life_construct2) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<Cell> l(in, 4, 3);

	EXPECT_EQ(l.width, 3);
	EXPECT_EQ(l.height, 4);
	EXPECT_EQ(l.board.size(), (l.width + 2) * (l.height + 2));

	EXPECT_EQ(l.board[0].acell->is_border(), true);
	EXPECT_EQ(l.board[1].acell->is_border(), true);
	EXPECT_EQ(l.board[2].acell->is_border(), true);
	EXPECT_EQ(l.board[3].acell->is_border(), true);
	EXPECT_EQ(l.board[4].acell->is_border(), true);

	EXPECT_EQ(l.board[5].acell->is_border(), true);
	EXPECT_EQ(l.board[6].acell->is_border(), false); EXPECT_EQ(l.board[6].acell->is_alive(), false);
	EXPECT_EQ(l.board[7].acell->is_border(), false); EXPECT_EQ(l.board[7].acell->is_alive(), false);
	EXPECT_EQ(l.board[8].acell->is_border(), false); EXPECT_EQ(l.board[8].acell->is_alive(), false);
	EXPECT_EQ(l.board[9].acell->is_border(), true);

	EXPECT_EQ(l.board[10].acell->is_border(), true);
	EXPECT_EQ(l.board[11].acell->is_border(), false); EXPECT_EQ(l.board[11].acell->is_alive(), false);
	EXPECT_EQ(l.board[12].acell->is_border(), false); EXPECT_EQ(l.board[12].acell->is_alive(), true);
	EXPECT_EQ(l.board[13].acell->is_border(), false); EXPECT_EQ(l.board[13].acell->is_alive(), false);
	EXPECT_EQ(l.board[14].acell->is_border(), true);

	EXPECT_EQ(l.board[15].acell->is_border(), true);
	EXPECT_EQ(l.board[16].acell->is_border(), false); EXPECT_EQ(l.board[16].acell->is_alive(), false);
	EXPECT_EQ(l.board[17].acell->is_border(), false); EXPECT_EQ(l.board[17].acell->is_alive(), false);
	EXPECT_EQ(l.board[18].acell->is_border(), false); EXPECT_EQ(l.board[18].acell->is_alive(), false);
	EXPECT_EQ(l.board[19].acell->is_border(), true);

	EXPECT_EQ(l.board[20].acell->is_border(), true);
	EXPECT_EQ(l.board[21].acell->is_border(), false); EXPECT_EQ(l.board[21].acell->is_alive(), true);
	EXPECT_EQ(l.board[22].acell->is_border(), false); EXPECT_EQ(l.board[22].acell->is_alive(), false);
	EXPECT_EQ(l.board[23].acell->is_border(), false); EXPECT_EQ(l.board[23].acell->is_alive(), false);
	EXPECT_EQ(l.board[24].acell->is_border(), true);

	EXPECT_EQ(l.board[25].acell->is_border(), true);
	EXPECT_EQ(l.board[26].acell->is_border(), true);
	EXPECT_EQ(l.board[27].acell->is_border(), true);
	EXPECT_EQ(l.board[28].acell->is_border(), true);
	EXPECT_EQ(l.board[29].acell->is_border(), true);
}

TEST(LifeFixture, life_construct3) {
	istringstream in("-1-\n0+3\n---\n45-\n\n");

	Life<FredkinCell> l(in, 4, 3);

	EXPECT_EQ(l.width, 3);
	EXPECT_EQ(l.height, 4);
	EXPECT_EQ(l.board.size(), (l.width + 2) * (l.height + 2));

	EXPECT_EQ(l.board[0].is_border(), true);
	EXPECT_EQ(l.board[1].is_border(), true);
	EXPECT_EQ(l.board[2].is_border(), true);
	EXPECT_EQ(l.board[3].is_border(), true);
	EXPECT_EQ(l.board[4].is_border(), true);

	EXPECT_EQ(l.board[5].is_border(), true);
	EXPECT_EQ(l.board[6].is_border(), false); EXPECT_EQ(l.board[6].is_alive(), false);
	EXPECT_EQ(l.board[7].is_border(), false); EXPECT_EQ(l.board[7].is_alive(), true); EXPECT_EQ(l.board[7].age(), 1);
	EXPECT_EQ(l.board[8].is_border(), false); EXPECT_EQ(l.board[8].is_alive(), false);
	EXPECT_EQ(l.board[9].is_border(), true);

	EXPECT_EQ(l.board[10].is_border(), true);
	EXPECT_EQ(l.board[11].is_border(), false); EXPECT_EQ(l.board[11].is_alive(), true); EXPECT_EQ(l.board[11].age(), 0);
	EXPECT_EQ(l.board[12].is_border(), false); EXPECT_EQ(l.board[12].is_alive(), true); EXPECT_GE(l.board[12].age(), 10);
	EXPECT_EQ(l.board[13].is_border(), false); EXPECT_EQ(l.board[13].is_alive(), true); EXPECT_EQ(l.board[13].age(), 3);
	EXPECT_EQ(l.board[14].is_border(), true);

	EXPECT_EQ(l.board[15].is_border(), true);
	EXPECT_EQ(l.board[16].is_border(), false); EXPECT_EQ(l.board[16].is_alive(), false);
	EXPECT_EQ(l.board[17].is_border(), false); EXPECT_EQ(l.board[17].is_alive(), false);
	EXPECT_EQ(l.board[18].is_border(), false); EXPECT_EQ(l.board[18].is_alive(), false);
	EXPECT_EQ(l.board[19].is_border(), true);

	EXPECT_EQ(l.board[20].is_border(), true);
	EXPECT_EQ(l.board[21].is_border(), false); EXPECT_EQ(l.board[21].is_alive(), true); EXPECT_EQ(l.board[21].age(), 4);
	EXPECT_EQ(l.board[22].is_border(), false); EXPECT_EQ(l.board[22].is_alive(), true); EXPECT_EQ(l.board[22].age(), 5);
	EXPECT_EQ(l.board[23].is_border(), false); EXPECT_EQ(l.board[23].is_alive(), false);
	EXPECT_EQ(l.board[24].is_border(), true);

	EXPECT_EQ(l.board[25].is_border(), true);
	EXPECT_EQ(l.board[26].is_border(), true);
	EXPECT_EQ(l.board[27].is_border(), true);
	EXPECT_EQ(l.board[28].is_border(), true);
	EXPECT_EQ(l.board[29].is_border(), true);
}

TEST(LifeFixture, life_at1) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in, 4, 3);

	ConwayCell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.is_alive(), false); ASSERT_EQ(c1.is_border(), false);

	ConwayCell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.is_alive(), true); ASSERT_EQ(c2.is_border(), false);

	ConwayCell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.is_alive(), false); ASSERT_EQ(c3.is_border(), false);

	ConwayCell& c4 = l.at(3, 0);
	ASSERT_EQ(c4.is_alive(), true); ASSERT_EQ(c4.is_border(), false);

}

TEST(LifeFixture, life_at2) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<Cell> l(in, 4, 3);

	Cell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.acell->is_alive(), false); ASSERT_EQ(c1.acell->is_border(), false);

	Cell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.acell->is_alive(), true); ASSERT_EQ(c2.acell->is_border(), false);

	Cell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.acell->is_alive(), false); ASSERT_EQ(c3.acell->is_border(), false);

	Cell& c4 = l.at(3, 0);
	ASSERT_EQ(c4.acell->is_alive(), true); ASSERT_EQ(c4.acell->is_border(), false);
}

TEST(LifeFixture, life_at3) {
	istringstream in("---\n-1-\n---\n+--\n\n");

	Life<FredkinCell> l(in, 4, 3);

	FredkinCell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.is_alive(), false); ASSERT_EQ(c1.is_border(), false);

	FredkinCell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.is_alive(), true); ASSERT_EQ(c2.is_border(), false);

	FredkinCell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.is_alive(), false); ASSERT_EQ(c3.is_border(), false);

	FredkinCell& c4 = l.at(3, 0);
	ASSERT_EQ(c4.is_alive(), true); ASSERT_EQ(c4.is_border(), false);
}

TEST(LifeFixture, life_const_at1) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in, 4, 3);

	const ConwayCell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.is_alive(), false); ASSERT_EQ(c1.is_border(), false);

	const ConwayCell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.is_alive(), true); ASSERT_EQ(c2.is_border(), false);

	const ConwayCell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.is_alive(), false); ASSERT_EQ(c3.is_border(), false);

}

TEST(LifeFixture, life_const_at2) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<Cell> l(in, 4, 3);

	const Cell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.acell->is_alive(), false); ASSERT_EQ(c1.acell->is_border(), false);

	const Cell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.acell->is_alive(), true); ASSERT_EQ(c2.acell->is_border(), false);

	const Cell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.acell->is_alive(), false); ASSERT_EQ(c3.acell->is_border(), false);
}

TEST(LifeFixture, life_const_at3) {
	istringstream in("---\n-1-\n---\n+--\n\n");

	Life<FredkinCell> l(in, 4, 3);

	const FredkinCell& c1 = l.at(0, 0);
	ASSERT_EQ(c1.is_alive(), false); ASSERT_EQ(c1.is_border(), false);

	const FredkinCell& c2 = l.at(1, 1);
	ASSERT_EQ(c2.is_alive(), true); ASSERT_EQ(c2.is_border(), false);

	const FredkinCell& c3 = l.at(2, 0);
	ASSERT_EQ(c3.is_alive(), false); ASSERT_EQ(c3.is_border(), false);

	const FredkinCell& c4 = l.at(3, 0);
	ASSERT_EQ(c4.is_alive(), true); ASSERT_EQ(c4.is_border(), false);
}

TEST(LifeFixture, life_evolve_all1) {
	istringstream in(".*.\n.*.\n.*.\n\n");

	Life<ConwayCell> l(in, 3, 3);

	l.evolve_all();

	ostringstream out;
	l.print(out);
	ASSERT_EQ(out.str(), "Generation = 1, Population = 3.\n...\n***\n...\n\n");
}

TEST(LifeFixture, life_evolve_all2) {
	istringstream in("---\n-1-\n---\n\n");

	Life<FredkinCell> l(in, 3, 3);

	l.evolve_all();

	ostringstream out;
	l.print(out);
	ASSERT_EQ(out.str(), "Generation = 1, Population = 4.\n-0-\n0-0\n-0-\n\n");
}

TEST(LifeFixture, life_evolve_all3) {
	istringstream in(".*.\n.*.\n.*.\n\n");

	Life<Cell> l(in, 3, 3);

	l.evolve_all();
	
	ostringstream out;
	l.print(out);
	ASSERT_EQ(out.str(), "Generation = 1, Population = 3.\n...\n***\n...\n\n");
}

TEST(LifeFixture, life_evolve_all4) {
	istringstream in(".*-5\n*.+-\n-.39\n.-*-\n\n");

	Life<Cell> l(in, 4, 4);

	l.evolve_all();
	
	ostringstream out;
	l.print(out);
	ASSERT_EQ(out.str(), "Generation = 1, Population = 9.\n.*0-\n..+0\n0.4+\n.0*-\n\n");
}

TEST(LifeFixture, life_evolve_all5) {
	istringstream in(".*-5\n*.+-\n-.19\n.-*-\n\n");

	Life<Cell> l(in, 4, 4);

	l.evolve_all();
	
	ostringstream out;
	l.print(out);
	ASSERT_EQ(out.str(), "Generation = 1, Population = 9.\n.*0-\n..+0\n0.*+\n.0*-\n\n");


}



TEST(LifeFixture, life_print1) {
	istringstream in(".*.\n.*.\n.*.\n\n");

	Life<ConwayCell> l(in, 3, 3);
	ostringstream s;
	l.print(s);
	ASSERT_EQ(s.str(), "Generation = 0, Population = 3.\n.*.\n.*.\n.*.\n\n");
}

TEST(LifeFixture, life_print2) {
	istringstream in("-1-\n2-4\n+--\n\n");

	Life<FredkinCell> l(in, 3, 3);
	ostringstream s;
	l.print(s);
	ASSERT_EQ(s.str(), "Generation = 0, Population = 4.\n-1-\n2-4\n+--\n\n");
}

TEST(LifeFixture, life_print3) {
	istringstream in("-1.\n*-4\n+--\n\n");

	Life<Cell> l(in, 3, 3);
	ostringstream s;
	l.print(s);
	ASSERT_EQ(s.str(), "Generation = 0, Population = 4.\n-1.\n*-4\n+--\n\n");

}

TEST(LifeFixture, life_begin1) {

	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in, 4, 3);

	Life<ConwayCell>::iterator<ConwayCell> c1 = l.begin();
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_begin2) {

	istringstream in("2..\n.*.\n...\n*..\n\n");

	Life<Cell> l(in, 4, 3);

	Life<Cell>::iterator<Cell> c1 = l.begin();
	ASSERT_EQ((*c1).acell->is_alive(), true); ASSERT_EQ((*c1).acell->is_border(), false);
	(*c1).~Cell();
	*c1 = Cell('.');
	++c1;
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);

	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
}

TEST(LifeFixture, life_begin3) {

	istringstream in("2--\n-3-\n---\n+--\n\n");

	Life<FredkinCell> l(in, 4, 3);

	Life<FredkinCell>::iterator<FredkinCell> c1 = l.begin();
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_end1) {

	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in, 4, 3);

	Life<ConwayCell>::iterator<ConwayCell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_end2) {

	istringstream in("2..\n.*.\n...\n*..\n\n");

	Life<Cell> l(in, 4, 3);

	Life<Cell>::iterator<Cell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), true); ASSERT_EQ((*c1).acell->is_border(), false);
	
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
}

TEST(LifeFixture, life_end3) {

	istringstream in("2--\n-3-\n---\n+--\n\n");

	Life<FredkinCell> l(in, 4, 3);

	Life<FredkinCell>::iterator<FredkinCell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_const_begin1) {

	istringstream in("...\n.*.\n...\n*..\n\n");

	const Life<ConwayCell> l(in, 4, 3);

	Life<ConwayCell>::const_iterator<ConwayCell> c1 = l.begin();
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_const_begin2) {

	istringstream in("2..\n.*.\n...\n*..\n\n");

	const Life<Cell> l(in, 4, 3);

	Life<Cell>::const_iterator<Cell> c1 = l.begin();
	ASSERT_EQ((*c1).acell->is_alive(), true); ASSERT_EQ((*c1).acell->is_border(), false);

	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	++c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
}

TEST(LifeFixture, life_const_begin3) {

	istringstream in("2--\n-3-\n---\n+--\n\n");

	const Life<FredkinCell> l(in, 4, 3);

	Life<FredkinCell>::const_iterator<FredkinCell> c1 = l.begin();
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	++c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_const_end1) {

	istringstream in("...\n.*.\n...\n*..\n\n");

	const Life<ConwayCell> l(in, 4, 3);

	Life<ConwayCell>::const_iterator<ConwayCell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

TEST(LifeFixture, life_const_end2) {

	istringstream in("2..\n.*.\n...\n*..\n\n");

	const Life<Cell> l(in, 4, 3);

	Life<Cell>::const_iterator<Cell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
	
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), true); ASSERT_EQ((*c1).acell->is_border(), false);
	
	--c1;
	ASSERT_EQ((*c1).acell->is_alive(), false); ASSERT_EQ((*c1).acell->is_border(), false);
} 

TEST(LifeFixture, life_const_end3) {

	istringstream in("2--\n-3-\n---\n+--\n\n");

	const Life<FredkinCell> l(in, 4, 3);

	Life<FredkinCell>::const_iterator<FredkinCell> c1 = l.end();
	--c1;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), true); ASSERT_EQ((*c1).is_border(), false);

	--c1;;
	ASSERT_EQ((*c1).is_alive(), false); ASSERT_EQ((*c1).is_border(), false);
}

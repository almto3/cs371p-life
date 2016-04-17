#include <sstream>
#include <vector>

#include "gtest/gtest.h"

#include "Life.h"

using namespace std;

TEST(ConwayFixture, conway_construct1) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.is_alive, true);
	ASSERT_EQ(c.is_border, false);
}

TEST(ConwayFixture, conway_construct2) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.is_alive, false);
	ASSERT_EQ(c.is_border, false);
}

TEST(ConwayFixture, conway_construct_border) {
	ConwayCell b = ConwayCell(true);
	ASSERT_EQ(b.is_border, true);
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


TEST(ConwayFixture, conway_copy1) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.is_alive, true);

	ConwayCell c2 = c;
	ASSERT_EQ(c2.is_alive, true);
}

TEST(ConwayFixture, conway_copy2) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.is_alive, false);

	ConwayCell c2 = c;
	ASSERT_EQ(c2.is_alive, false);
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

	vector<Cell> neighbors;
	for (char c : param) {
		neighbors.push_back(Cell(new ConwayCell(c)));
	}

	ConwayCell c = ConwayCell(cell_value);
	Cell c2 = c.evolve(neighbors);

	ostringstream s;
	c2.acell->print(s);
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
	ASSERT_EQ(f.is_alive, false);
	ASSERT_EQ(f.is_border, false);
	ASSERT_EQ(f.age, 0);
}

TEST(FredkinFixture, fredkin_construct2) {
	FredkinCell f = FredkinCell('0');
	ASSERT_EQ(f.is_alive, true);
	ASSERT_EQ(f.is_border, false);
	ASSERT_EQ(f.age, 0);
}

TEST(FredkinFixture, fredkin_construct3) {
	FredkinCell f = FredkinCell('5');
	ASSERT_EQ(f.is_alive, true);
	ASSERT_EQ(f.is_border, false);
	ASSERT_EQ(f.age, 5);
}

TEST(FredkinFixture, fredkin_construct4) {
	FredkinCell f = FredkinCell('9');
	ASSERT_EQ(f.is_alive, true);
	ASSERT_EQ(f.is_border, false);
	ASSERT_EQ(f.age, 9);
}

TEST(FredkinFixture, fredkin_construct5) {
	FredkinCell f = FredkinCell('+');
	ASSERT_EQ(f.is_alive, true);
	ASSERT_EQ(f.is_border, false);
	ASSERT_GE(f.age, 10);
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

	vector<Cell> neighbors;
	for (char c : param) {
		neighbors.push_back(Cell(new FredkinCell(c)));
	}

	FredkinCell c = FredkinCell(cell_value);
	Cell c2 = c.evolve(neighbors);

	ostringstream s;
	c2.acell->print(s);
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
	vector<char>({'2', '-', '-', '-', '-', '-', '-', '-',   '3', '4'}),
	vector<char>({'2', '2', '-', '-', '-', '-', '-', '-',   '8', '-'}),
	vector<char>({'2', '2', '2', '-', '-', '-', '-', '-',   '9', '+'}),
	vector<char>({'2', '2', '2', '2', '-', '-', '-', '-',   '4', '-'}),

	vector<char>({'-', '-', '-', '-', '2', '-', '4', '-',   '5', '-'}),
	vector<char>({'6', '-', '-', '-', '-', '5', '-', '-',   '+', '+'}),
	vector<char>({'2', '5', '-', '-', '3', '-', '-', '1',   '2', '-'}),
	vector<char>({'2', '8', '2', '-', '0', '-', '5', '-',   '5', '6'}),
	vector<char>({'1', '2', '+', '2', '3', '4', '-', '-',   '0', '-'})
	));

// TODO: test when FredkinCells and ConwayCells border each other

// --------
// CellTest
// --------

TEST(CellFixture, cell_conway_copy_constructor1) {
	ConwayCell* cc = new ConwayCell('*');
	ASSERT_EQ(cc->is_alive, true);

	Cell c = Cell(cc);
	ASSERT_EQ(c.acell->is_alive, true);

	Cell c2 = c;
	delete cc;
	ASSERT_EQ(c2.acell->is_alive, true);
}

TEST(CellFixture, cell_conway_copy_constructor2) {
	ConwayCell* cc = new ConwayCell('.');
	ASSERT_EQ(cc->is_alive, false);

	Cell c = Cell(cc);
	ASSERT_EQ(c.acell->is_alive, false);

	Cell c2 = c;
	delete cc;
	ASSERT_EQ(c2.acell->is_alive, false);
}

TEST(CellFixture, cell_conway_copy_assignment1) {
	ConwayCell* cc = new ConwayCell('*');
	ASSERT_EQ(cc->is_alive, true);

	ConwayCell* cc2 = new ConwayCell('.');
	ASSERT_EQ(cc2->is_alive, false);

	Cell c = Cell(cc);
	ASSERT_EQ(c.acell->is_alive, true);

	Cell c2 = Cell(cc2);
	c2 = c;
	delete cc;
	ASSERT_EQ(c2.acell->is_alive, true);
}

TEST(CellFixture, cell_conway_copy_assignment2) {
	ConwayCell* cc = new ConwayCell('.');
	ASSERT_EQ(cc->is_alive, false);

	ConwayCell* cc2 = new ConwayCell('*');
	ASSERT_EQ(cc2->is_alive, true);

	Cell c = Cell(cc);
	ASSERT_EQ(c.acell->is_alive, false);

	Cell c2 = Cell(cc2);
	c2 = c;
	delete cc;
	ASSERT_EQ(c2.acell->is_alive, false);
}

// --------
// LifeTest
// --------

TEST(LifeFixture, life_construct1) {
	istringstream in("...\n.*.\n...\n*..\n\n");

	Life<ConwayCell> l(in);

	EXPECT_EQ(l.width, 3);
	EXPECT_EQ(l.height, 4);
	EXPECT_EQ(l.board.size(), (l.width + 2) * (l.height + 2));

	EXPECT_EQ(l.board[0].acell->is_border, true);
	EXPECT_EQ(l.board[1].acell->is_border, true);
	EXPECT_EQ(l.board[2].acell->is_border, true);
	EXPECT_EQ(l.board[3].acell->is_border, true);
	EXPECT_EQ(l.board[4].acell->is_border, true);

	EXPECT_EQ(l.board[5].acell->is_border, true);
	EXPECT_EQ(l.board[6].acell->is_border, false); EXPECT_EQ(l.board[6].acell->is_alive, false);
	EXPECT_EQ(l.board[7].acell->is_border, false); EXPECT_EQ(l.board[6].acell->is_alive, false);
	EXPECT_EQ(l.board[8].acell->is_border, false); EXPECT_EQ(l.board[6].acell->is_alive, false);
	EXPECT_EQ(l.board[9].acell->is_border, true);

	EXPECT_EQ(l.board[10].acell->is_border, true);
	EXPECT_EQ(l.board[11].acell->is_border, false); EXPECT_EQ(l.board[11].acell->is_alive, false);
	EXPECT_EQ(l.board[12].acell->is_border, false); EXPECT_EQ(l.board[12].acell->is_alive, true);
	EXPECT_EQ(l.board[13].acell->is_border, false); EXPECT_EQ(l.board[13].acell->is_alive, false);
	EXPECT_EQ(l.board[14].acell->is_border, true);

	EXPECT_EQ(l.board[15].acell->is_border, true);
	EXPECT_EQ(l.board[16].acell->is_border, false); EXPECT_EQ(l.board[16].acell->is_alive, false);
	EXPECT_EQ(l.board[17].acell->is_border, false); EXPECT_EQ(l.board[17].acell->is_alive, false);
	EXPECT_EQ(l.board[18].acell->is_border, false); EXPECT_EQ(l.board[18].acell->is_alive, false);
	EXPECT_EQ(l.board[19].acell->is_border, true);

	EXPECT_EQ(l.board[20].acell->is_border, true);
	EXPECT_EQ(l.board[21].acell->is_border, false); EXPECT_EQ(l.board[21].acell->is_alive, true);
	EXPECT_EQ(l.board[22].acell->is_border, false); EXPECT_EQ(l.board[22].acell->is_alive, false);
	EXPECT_EQ(l.board[23].acell->is_border, false); EXPECT_EQ(l.board[23].acell->is_alive, false);
	EXPECT_EQ(l.board[24].acell->is_border, true);

	EXPECT_EQ(l.board[25].acell->is_border, true);
	EXPECT_EQ(l.board[26].acell->is_border, true);
	EXPECT_EQ(l.board[27].acell->is_border, true);
	EXPECT_EQ(l.board[28].acell->is_border, true);
	EXPECT_EQ(l.board[29].acell->is_border, true);
}
/*
TEST(LifeFixture, life_print1) {

}

TEST(LifeFixture, life_evolve1) {

}

TEST(LifeFixture, life_begin1) {

}

TEST(LifeFixture, life_end1) {

}

TEST(LifeFixture, life_at1) {

}
*/

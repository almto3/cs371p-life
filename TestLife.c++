#include <sstream>
#include <vector>

#include "gtest/gtest.h"

#include "Life.h"

using namespace std;

TEST(ConwayFixture, conway_construct1) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.alive, true);
}

TEST(ConwayFixture, conway_construct2) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.alive, false);
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
	ASSERT_EQ(f.alive, false);
	ASSERT_EQ(f.age, 0);
}

TEST(FredkinFixture, fredkin_construct2) {
	FredkinCell f = FredkinCell('0');
	ASSERT_EQ(f.alive, true);
	ASSERT_EQ(f.age, 0);
}

TEST(FredkinFixture, fredkin_construct3) {
	FredkinCell f = FredkinCell('5');
	ASSERT_EQ(f.alive, true);
	ASSERT_EQ(f.age, 5);
}

TEST(FredkinFixture, fredkin_construct4) {
	FredkinCell f = FredkinCell('9');
	ASSERT_EQ(f.alive, true);
	ASSERT_EQ(f.age, 9);
}

TEST(FredkinFixture, fredkin_construct5) {
	FredkinCell f = FredkinCell('+');
	ASSERT_EQ(f.alive, true);
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
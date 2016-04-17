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


class EvolutionFixture : public ::testing::TestWithParam<vector<char>> {
	// Fixture for running tests of evolution. The argument is a vector containing the neighbors, then the value of the cell, then the expected value
};

TEST_P(EvolutionFixture, conway_evolve) {
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

INSTANTIATE_TEST_CASE_P(ConwayEvolutionAlive, EvolutionFixture, ::testing::Values(
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

INSTANTIATE_TEST_CASE_P(ConwayEvolutionDead, EvolutionFixture, ::testing::Values(
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
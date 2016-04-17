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


//class EvolutionFixture : public ::testing::TestWithParam<char> {
//
//}

TEST(ConwayFixture, conway_evolve0_alive) {
	vector<Cell> neighbors { Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')), Cell(new ConwayCell('.')) };

	ConwayCell c = ConwayCell('*');
	Cell c2 = c.evolve(neighbors);

	ostringstream s;
	c2.acell->print(s);
	ASSERT_EQ(s.str(), ".");
}

/*
TEST(ConwayFixture, conway_evolve1_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve(neighbors);
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve2_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve(neighbors);
	ASSERT_EQ(c2.alive, true);
}

TEST(ConwayFixture, conway_evolve3_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve(neighbors);
	ASSERT_EQ(c2.alive, true);
}

TEST(ConwayFixture, conway_evolve4_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve5_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve6_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve7_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve8_alive) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*') };
	ConwayCell c = ConwayCell('*');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}


TEST(ConwayFixture, conway_evolve0_dead) {
	vector<Cell> neighbors { ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve1_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve2_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve3_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, true);
}

TEST(ConwayFixture, conway_evolve4_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve5_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve6_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve7_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('.') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}

TEST(ConwayFixture, conway_evolve8_dead) {
	vector<Cell> neighbors { ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*'), ConwayCell('*') };
	ConwayCell c = ConwayCell('.');
	ConwayCell c2 = c.evolve();
	ASSERT_EQ(c2.alive, false);
}
*/

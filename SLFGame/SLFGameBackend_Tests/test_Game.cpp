#include "gmock/gmock.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/DataTypes.h"

TEST(TestGame, CalculatePoints_2solo2multi2same_PointOutputEQ70)
{
	Game game{};
	std::vector<int> decisions = { 1,1,2,2,3,3 };

	int actual = game.CalculatePoints(decisions);
	int expected = 70;


	EXPECT_EQ(expected, actual);
}
#include "gmock/gmock.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/DataTypes.h"

class FakeClass
{
public:
	MOCK_METHOD(void, Prepare, ());
	MOCK_METHOD(void, End, ());
};

TEST(TestGame, CalculatePoints_2solo2multi2same_PointOutputEQ70)
{
	Game game{};
	std::vector<int> decisions = { 1,1,2,2,3,3 };

	int actual = game.CalculatePoints(decisions);
	int expected = 70;


	EXPECT_EQ(expected, actual);
}

TEST(TestGame, CheckGameFinished_3currentRound5MaxRound_ExpectCallPrepare)
{
	GameStats gs{};
	Game game{};
	FakeClass fc{};

	gs.SetCurrentRound(3);
	gs.SetMaxRounds(5);

	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	game.onGameOver = [&fc]() {fc.End(); };

	game.CheckGameFinished(gs);


	EXPECT_CALL(fc, Prepare());
}

TEST(TestGame, CheckGameFinished_6currentRound5MaxRound_ExpectCallEnd)
{
	GameStats gs;
	Game game;
	FakeClass fc;

	gs.SetCurrentRound(6);
	gs.SetMaxRounds(5);

	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	game.onGameOver = [&fc]() {fc.End(); };

	game.CheckGameFinished(gs);

	EXPECT_CALL(fc, End());
}
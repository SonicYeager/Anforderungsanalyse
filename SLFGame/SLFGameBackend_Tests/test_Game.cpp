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
	std::vector<DECISION> decisions{ SOLO, SOLO, UNIQUE, UNIQUE, MULTIPLE, MULTIPLE };

	int actual = game.CalculatePoints(decisions);
	int expected = 70;


	EXPECT_EQ(expected, actual);
}

TEST(TestGame, CheckGameFinished_3currentRound5MaxRound_ExpectCallPrepare)
{
	GameStats gs{};
	Game game{};
	::testing::StrictMock<FakeClass> fc{};
	::testing::InSequence sq;

	gs.SetCurrentRound(3);
	gs.SetMaxRounds(5);

	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	game.onGameOver = [&fc]() {fc.End(); };
	EXPECT_CALL(fc, Prepare());

	game.CheckGameFinished(gs);
}

TEST(TestGame, CheckGameFinished_6currentRound5MaxRound_ExpectCallEnd)
{
	GameStats gs;
	Game game;
	::testing::StrictMock<FakeClass> fc;
	::testing::InSequence sq;

	gs.SetCurrentRound(6);
	gs.SetMaxRounds(5);

	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	game.onGameOver = [&fc]() {fc.End(); };
	EXPECT_CALL(fc, End());

	game.CheckGameFinished(gs);
}
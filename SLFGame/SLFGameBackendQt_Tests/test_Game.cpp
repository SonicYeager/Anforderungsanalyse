#include "gmock/gmock.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/DataTypes.h"

class FakeClass
{
public:
	MOCK_METHOD(void, Prepare, ());
	MOCK_METHOD(void, End, ());
};

TEST(TestGame, CalculatePoints_2players)
{
	Game game{};
	Game expect{};

	game.m_GameStats.categories.push_back("Stadt");
	game.m_GameStats.categories.push_back("Land");
	game.m_GameStats.categories.push_back("Fluss");
	game.m_GameStats.players.emplace(0, PlayerStats{ "Klaus", 0, {"Arnsberg","Argentinien","Amsel"} });
	game.m_GameStats.players.emplace(1, PlayerStats{ "Peter", 0, {"Arnsberg","Armenien",""} });
	game.m_GameStats.votes = { DDDVector{  {  {true,true},{true,true}  },{ {true,true},{true,true} }, { {true,true},{false,false} } } };
	game.CalculatePoints(game.m_GameStats.votes);

	expect.m_GameStats.players.emplace(0, PlayerStats{ "Klaus", 35, {"Arnsberg","Argentinien","Amsel"} });
	expect.m_GameStats.players.emplace(1, PlayerStats{ "Peter", 15, {"Arnsberg","Armenien",""} });

	EXPECT_EQ(game.m_GameStats.players, expect.m_GameStats.players);
}

TEST(TestGame, CheckGameFinished_3currentRound5MaxRound_ExpectCallPrepare)
{
	GameStats gs{};
	Game game{};
	::testing::StrictMock<FakeClass> fc{};
	::testing::InSequence sq;

	gs.currentRound = 3;
	gs.maxRounds = 5;

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

	gs.currentRound= 6;
	gs.maxRounds = 5;

	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	game.onGameOver = [&fc]() {fc.End(); };
	EXPECT_CALL(fc, End());

	game.CheckGameFinished(gs);
}

//extend pls
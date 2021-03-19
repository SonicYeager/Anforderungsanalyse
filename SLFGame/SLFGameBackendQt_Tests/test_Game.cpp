#include "gmock/gmock.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/DataTypes.h"

class FakeClass
{
public:
	MOCK_METHOD(void, Prepare, (const std::string&, const Letters&));
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
	Game game{};
	game.m_GameStats.maxRounds = 5;
	game.m_GameStats.currentRound = 0;

	::testing::NiceMock<FakeClass> fc{};
	::testing::InSequence sq;


	std::string _s = { "Stadt,Land,Fluss,Name,Tier,Beruf" };
	Letters _l{};

	//game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
	//game.onGameOver = [&fc]() {fc.End(); };

	auto onprepround = [&](const std::string& s, const Letters& l) 
	{
		_s = s; 
		_l = l; 
		fc.Prepare(s, l);
	};
	EXPECT_CALL(fc, Prepare(_s, _l));

	game.CheckGameFinished(onprepround);
}

//TEST(TestGame, CheckGameFinished_6currentRound5MaxRound_ExpectCallEnd)
//{
//	GameStats gs;
//	Game game;
//	::testing::StrictMock<FakeClass> fc;
//	::testing::InSequence sq;
//
//	gs.currentRound= 6;
//	gs.maxRounds = 5;
//
//	game.onPrepareNextRound = [&fc]() {fc.Prepare(); };
//	game.onGameOver = [&fc]() {fc.End(); };
//	EXPECT_CALL(fc, End());
//
//	game.CheckGameFinished(gs);
//}
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

	game.CheckGameFinished(onprepround, [](const std::map<int, PlayerStats>&) {});
}

TEST(TestGame, ClearPlayerAnswers_ThreePlayersWithAnswers_NoAnswers)
{
	Game game{};
	PlayerStats ps{ "Checker", 0, {"Some", "Answers", "Given"} };
	game.m_GameStats.players.emplace(0, ps);
	game.m_GameStats.players.emplace(1, ps);
	game.m_GameStats.players.emplace(3, ps);

	game.ClearPlayerAnswers();

	EXPECT_EQ(game.m_GameStats.players[0].answers, Categories{});
	EXPECT_EQ(game.m_GameStats.players[1].answers, Categories{});
	EXPECT_EQ(game.m_GameStats.players[3].answers, Categories{});
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

TEST(TestGame, HandleGameStats_FINALSCORES_CallOnFinalScores)
{
	Game game{};
	bool actual = false;

	auto onSetupRound = [](const std::string&, const Letters&) {};
	auto onStandart = [](GameState) {};
	auto onFinalRound = [&actual](const std::map<int, PlayerStats>&) {actual = true; };

	game.HandleGameState(STATE::FINALSCORES, onSetupRound, onFinalRound ,onStandart);

	EXPECT_TRUE(actual);
}

TEST(TestGame, HandleGameStats_ROUNDOVER_AnswersClearedPointsCalced)
{
	Game game{};
	auto onSetupRound = [](const std::string&, const Letters&) {};
	auto onStandart = [](GameState) {};
	auto onFinalRound = [](const std::map<int, PlayerStats>&) { };
	game.m_GameStats.categories = {"Verb", "Substantiv"};
	game.m_GameStats.players.emplace(1, PlayerStats{ "Dredd", 0, {"Some", "Traitors"} });
	game.m_GameStats.players.emplace(2, PlayerStats{ "Cassandra", 0, {"Some", "Fools"} });
	game.m_GameStats.votes = { {{true}, {true}}, { {true}, {true}} };

	game.HandleGameState(STATE::ROUNDOVER, onSetupRound, onFinalRound, onStandart);

	EXPECT_EQ(game.m_GameStats.players[1].points, 15);
	EXPECT_EQ(game.m_GameStats.players[2].points, 15);
	EXPECT_EQ(game.m_GameStats.players[2].answers, Categories{});
	EXPECT_EQ(game.m_GameStats.players[2].answers, Categories{});
}
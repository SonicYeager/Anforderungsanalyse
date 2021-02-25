#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, Init, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareGame, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&, const PlayerStats&), (override));
};

class FakeRandomLetterGenerator : public RandomGenRessource
{
public:
	Letter GenerateLetter() override
	{
		auto res = numCalls == 1 ? Letter{ 'B' } : Letter{ 'C' };
		++numCalls;
		return res;
	}
	Letter GenerateUnusedLetter(const Letters& filter) override
	{
		auto res = numCalls == 1 ? Letter{ 'B' } : Letter{ 'C' };
		++numCalls;
		return res;
	}
private:
	int numCalls = 0;
};

class FakeNetworkSource : public NetworkSource
{
public:
	std::string GenerateLobbyCode() override
	{
		return "CODE";
	}
private:
	int numCalls = 0;
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gi{&frlg, &gsop, &g, &fns, &p}
	{}
protected:
	virtual void SetUp()
	{
		Test::SetUp();
	}
	virtual void TearDown()
	{
		Test::TearDown();
	}

	Game g{};
	FakeRandomLetterGenerator frlg{};
	FakeNetworkSource fns{};
	GameStatsOperations gsop{};
	GameInteractor gi;
	GameStats gs{};
	PlayerStats ps{};
	SLFParser p;
};

TEST_F(TestGameInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
{
	auto actual = gi.PrepareLobby();

	EXPECT_EQ(actual.second.GetAnswers().size(), 0);
	EXPECT_EQ(actual.second.GetPoints(), 0);

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual.first.GetCategories(), cat);
	EXPECT_EQ(actual.first.GetCurrentLetter(), Letter{});
	EXPECT_EQ(actual.first.GetUsedLetters().letters.size(), 0);
	EXPECT_EQ(actual.first.GetCurrentRound(), 0);
	EXPECT_EQ(actual.first.GetMaxRound(), 5);
	EXPECT_EQ(actual.first.GetLobbyCode(), "CODE");
}

TEST_F(TestGameInteractor, PrepareGame_StandartCatsRound0NoTimer_ReturnGameStatsAndPlayerStatsFilledWithStdCatsRound0NoTimer)
{
	GameStats actualGS;
	PlayerStats actualPS;
	gi.onPrepareGame = [&actualGS, &actualPS](GameStats gs, PlayerStats ps) 
	{
		actualGS = gs;
		actualPS = ps;
	};

	gi.PrepareGame("Stadt,Land,Fluss,Name,Tier,Beruf", "", "0");

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actualGS.GetCategories(), cat);
	EXPECT_EQ(actualGS.GetTimeout(), "");
	EXPECT_EQ(actualGS.GetCurrentRound(), 1);
}

TEST_F(TestGameInteractor, PrepareOverview_AnswersBremenBulgarienBrahmaputra_ReturnPlayerStatsFilledWithBremenBulgarienBrahmaputra)
{
	GameStats actualGS;
	PlayerStats actualPS;
	gi.onPrepareOverview = [&actualGS, &actualPS](GameStats gs, PlayerStats ps)
	{
		actualGS = gs;
		actualPS = ps;
	};

	gi.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} });

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualPS.GetAnswers(), expected);
}

TEST_F(TestGameInteractor, EndRound_OneFromZeroRoundsWith40Points_CallGSWithRoundZeroFromZeroAndPSwith40Points)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	PlayerStats expectedPS;
	expectedPS.SetPoints(40);
	::testing::StrictMock<FakeUI> fui;
	gi.onGameOver = [&fui](GameStats gs, PlayerStats ps) {fui.PrepareFinalScores(gs, ps); };
	std::vector<int> dec{2, 2, 1};

	EXPECT_CALL(fui, PrepareFinalScores(expectedGS, expectedPS));

	gi.EndRound(dec);
}

TEST_F(TestGameInteractor, EndRound_ZeroFrom2RoundsWith40Points_CallGSWithRound1From2AndPSwith40Points)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	expectedGS.SetCurrentLetter({'C'});
	expectedGS.SetMaxRounds(2);
	PlayerStats expectedPS;
	expectedPS.SetPoints(40);
	::testing::StrictMock<FakeUI> fui;
	gi.onPrepareNextRound = [&fui](GameStats gs, PlayerStats ps) {fui.PrepareGame(gs, ps); };
	std::vector<int> dec{ 2, 2, 1 };
	gi.m_GameStats.SetMaxRounds(2);

	EXPECT_CALL(fui, PrepareGame(expectedGS, expectedPS));

	gi.EndRound(dec);
}
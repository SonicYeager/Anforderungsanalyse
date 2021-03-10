#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/ClientSource.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, PrepareLobby, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareGame, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&), (override));
	MOCK_METHOD(void, UpdateGameStats, (const GameStats&), (override));
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

class FakeClient : public ClientSource
{
public:
	MOCK_METHOD(std::string, GenerateLobbyCode, (), (override));
	MOCK_METHOD(void, ConnectToServer, (const LobbyCode&), (override));
	MOCK_METHOD(void, WriteToHost, (const ByteStream&), (override));
};

class TestClientInteractor : public Test
{
public:
	TestClientInteractor() :
		gameInteractor{ &fakeRandomLetterGenerator, &gameStatsOperations, &game, &parser, &fakeServer, &serializer, &msgHandler }
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

	Game game{};
	FakeRandomLetterGenerator fakeRandomLetterGenerator{};
	::testing::NiceMock<FakeClient> fakeServer{};
	GameStatsOperations gameStatsOperations{};
	GameStats gameStats{};
	PlayerStats playerStats{};
	SLFParser parser;
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ClientInteractorImpl gameInteractor;
};

TEST_F(TestClientInteractor, Enjoy)
{
	auto actual = gameInteractor.PrepareLobby();

	EXPECT_EQ(actual.second.answers.size(), 0);
	EXPECT_EQ(actual.second.points, 0);

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual.first.categories, cat);
	EXPECT_EQ(actual.first.currentLetter, Letter{});
	EXPECT_EQ(actual.first.lettersUsed.size(), 0);
	EXPECT_EQ(actual.first.currentRound, 0);
	EXPECT_EQ(actual.first.maxRounds, 5);
	EXPECT_EQ(actual.first.lobbyCode, "");
}
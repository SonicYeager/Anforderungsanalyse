#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/DataTypes.h"

TEST(TestGameStatsOperations, InkrementRound_GameStatsZeroRounds_GameStatsOneRound)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.InkrementRound(gs);

	EXPECT_EQ(gs.currentRound, 1);

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedEmpty_GameStatsLettersUsedFilledWithC)
{

	GameStatsOperations gso{};
	GameStats gs{};
	gs.currentLetter = {'C'};

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.lettersUsed[0], 'C');

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedFilledWithC_GameStatsLettersUsedFilledWithCD)
{

	GameStatsOperations gso{};
	GameStats gs{};
	gs.currentLetter = { 'D' };
	Letters letters{{{'C'}}};
	gs.lettersUsed = letters;

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.lettersUsed[1], 'D');

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedEmptyCurrentLetterIsEmpty_GameStatsLettersUsedFilledWithNone)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.lettersUsed.size(), 0);

}

TEST(TestGameStatsOperations, SetNewLetter_GameStatsCurrentLetterEmpty_GameStatsCurrentLettersIsC)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.SetNewLetter(Letter{'C'}, gs);

	EXPECT_EQ(gs.currentLetter, 'C');

}

TEST(TestGameStatsOperations, LetterIsAlreadyUsed_IsNotUsed_ReturnFalse)
{

	GameStatsOperations gso{};
	GameStats gs{};

	auto actual = gso.LetterIsAlreadyUsed(Letter{ 'C' }, Letters{ {Letter{ 'A' }, Letter{'B'}} });

	EXPECT_FALSE(actual);

}

TEST(TestGameStatsOperations, LetterIsAlreadyUsed_IsUsed_ReturnTrue)
{

	GameStatsOperations gso{};
	GameStats gs{};

	auto actual = gso.LetterIsAlreadyUsed(Letter{ 'B' }, Letters{ {Letter{ 'A' }, Letter{'B'}} });

	EXPECT_TRUE(actual);

}

//TEST(TestGameStatsOperations, CreateStats_LobbyCode0c346bv_ReturnConfiguredGameStatsAndPlayerStats)
//{
//
//	GameStatsOperations gso{};
//	GameStats gs{};
//
//	auto actual = gso.CreateStats("0c346bv", "");
//
//	GameStats expectedgs{};
//	PlayerStats expectedps{};
//	expectedgs.maxRounds = 5;
//	expectedgs.categories = {{"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"}};
//	expectedgs.lobbyCode = "0c346bv";
//	EXPECT_EQ(actual, expectedgs);
//	EXPECT_EQ(actual.players[0], expectedps);
//
//}

TEST(TestGameStatsOperations, SetAnswers_BaumBerlinBen_SetToBaumBerlinBen)
{
	GameStatsOperations gso{};
	PlayerStats playerStats{};
	std::vector<std::string> answers{ {"Baum"}, {"Berlin"}, {"Ben"} };

	gso.SetAnswers(answers, playerStats);


	EXPECT_EQ(playerStats.answers, answers);

}

TEST(TestGameStatsOperations, AddPoints_65_SetTo65)
{
	GameStatsOperations gso{};
	PlayerStats playerStats{};
	int points = 65;

	gso.AddPoints(65, playerStats);


	EXPECT_EQ(playerStats.points, points);

}


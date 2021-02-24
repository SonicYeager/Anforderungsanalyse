#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/DataTypes.h"

TEST(TestGameStatsOperations, InkrementRound_GameStatsZeroRounds_GameStatsOneRound)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.InkrementRound(gs);

	EXPECT_EQ(gs.GetCurrentRound(), 1);

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedEmpty_GameStatsLettersUsedFilledWithC)
{

	GameStatsOperations gso{};
	GameStats gs{};
	gs.SetCurrentLetter(Letter{'C'});

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.GetUsedLetters().letters[0].letter, 'C');

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedFilledWithC_GameStatsLettersUsedFilledWithCD)
{

	GameStatsOperations gso{};
	GameStats gs{};
	gs.SetCurrentLetter(Letter{ 'D' });
	Letters letters{{{'C'}}};
	gs.SetUsedLetters(letters);

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.GetUsedLetters().letters[1].letter, 'D');

}

TEST(TestGameStatsOperations, AddPreviousLetter_GameStatsLettersUsedEmptyCurrentLetterIsEmpty_GameStatsLettersUsedFilledWithNone)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.AddPreviousLetter(gs);

	EXPECT_EQ(gs.GetUsedLetters().letters.size(), 0);

}

TEST(TestGameStatsOperations, SetNewLetter_GameStatsCurrentLetterEmpty_GameStatsCurrentLettersIsC)
{

	GameStatsOperations gso{};
	GameStats gs{};

	gso.SetNewLetter(Letter{'C'}, gs);

	EXPECT_EQ(gs.GetCurrentLetter().letter, 'C');

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

TEST(TestGameStatsOperations, CreateStats_LobbyCode0c346bv_ReturnConfiguredGameStatsAndPlayerStats)
{

	GameStatsOperations gso{};
	GameStats gs{};

	auto actual = gso.CreateStats("0c346bv");

	GameStats expectedgs{};
	PlayerStats expectedps{};
	expectedgs.SetMaxRounds(5);
	expectedgs.SetCategories({{{"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"}}});
	expectedgs.SetLobbyCode("0c346bv");
	EXPECT_EQ(actual.first, expectedgs);
	EXPECT_EQ(actual.second, expectedps);

}

TEST(TestGameStatsOperations, SetAnswers_BaumBerlinBen_SetToBaumBerlinBen)
{
	GameStatsOperations gso{};
	PlayerStats ps{};
	std::vector<std::string> answers{ {"Baum"}, {"Berlin"}, {"Ben"} };

	gso.SetAnswers(answers, ps);


	EXPECT_EQ(ps.GetAnswers(), answers);

}

TEST(TestGameStatsOperations, AddPoints_65_SetTo65)
{
	GameStatsOperations gso{};
	PlayerStats ps{};
	int points = 65;

	gso.AddPoints(65, ps);


	EXPECT_EQ(ps.GetPoints(), points);

}


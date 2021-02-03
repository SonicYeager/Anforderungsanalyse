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
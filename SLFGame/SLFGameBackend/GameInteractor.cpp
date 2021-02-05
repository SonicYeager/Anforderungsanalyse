#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op) :
	mp_rand(gen), 
	mp_op(op)
{}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareNextRound(const GameStats& gs, const PlayerStats& ps)
{
	FileHandler fh;
	fh.SetFolder("./");
	fh.LoadFile("categories.txt");
	auto changedgs = gs;
        auto allLines = fh.ReturnAllLines();
        changedgs.SetCategories(allLines);

	mp_op->InkrementRound(changedgs);
	mp_op->AddPreviousLetter(changedgs);
	Letter generated;
	do 
	{
		generated = mp_rand->GenerateLetter();
	} while (mp_op->LetterIsAlreadyUsed(generated, changedgs.GetUsedLetters()));
	mp_op->SetNewLetter(generated, changedgs);
	return std::make_pair(changedgs, ps);
}

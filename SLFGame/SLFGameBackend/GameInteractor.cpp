#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, NetworkSource* n) :
	mp_rand(gen), 
	mp_op(op), 
	mp_n(n)
{}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareNextRound(const GameStats& gs, const PlayerStats& ps)
{
	auto changedgs = gs;

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

std::pair<GameStats, PlayerStats> GameInteractor::PrepareLobby(const std::string& lobbyCode)
{
	auto code = mp_n->GenerateLobbyCode();
	return mp_op->CreateStats(code);
}

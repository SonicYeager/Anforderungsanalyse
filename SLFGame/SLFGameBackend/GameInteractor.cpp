#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, NetworkSource* n, SLFParser* p) :
	mp_rand(gen), 
	mp_op(op), 
	mp_n(n),
	mp_p(p)
{}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
{
	GameStats gs;
	PlayerStats ps;
	auto parsedCats = mp_p->ParseCategories(cats);
	gs.SetCategories(parsedCats);
	auto parsedRound = mp_p->ParseRoundCount(roundCount);
	gs.SetCurrentRound(parsedRound);
	gs.SetTimeout(roundTime);
	gs.SetCurrentRound(0);
	mp_op->InkrementRound(gs);
	gs.SetMaxRounds(parsedRound);
	Letter generated;
	do 
	{
		generated = mp_rand->GenerateLetter();
	} while (mp_op->LetterIsAlreadyUsed(generated, gs.GetUsedLetters()));
	mp_op->SetNewLetter(generated, gs);
	onPrepareNextRound(gs, ps);
	return std::make_pair(gs, ps);
}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareLobby(const std::string& lobbyCode)
{
	auto code = mp_n->GenerateLobbyCode();
	return mp_op->CreateStats(code);
}

#pragma once
#include "DataTypes.h"

class DataOperationLogic
{
public:
	virtual ~DataOperationLogic() = default;

	virtual void		InkrementRound		(GameStats&)									= 0;
	virtual void		AddPreviousLetter	(GameStats&)									= 0;
	virtual void		SetNewLetter		(Letter, GameStats&)							= 0;
	virtual bool		LetterIsAlreadyUsed	(Letter, Letters)								= 0;
	virtual void		AddPoints			(const int, PlayerStats&)						= 0;
	virtual void		SetAnswers			(const std::vector<std::string>&, PlayerStats&) = 0;
	virtual void		SetPlayerName		(const std::string&, int, GameStats&)				= 0;
	virtual GameStats	CreateStats			(const std::string&, const std::string&)		= 0;
};
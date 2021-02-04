#pragma once
#include "DataTypes.h"

class DataOperationLogic
{
public:
	virtual void InkrementRound(GameStats&) = 0;
	virtual void AddPreviousLetter(GameStats&) = 0;
	virtual void SetNewLetter(Letter, GameStats&) = 0;
	virtual bool LetterIsAlreadyUsed(Letter, Letters) = 0;
	virtual ~DataOperationLogic() = default;
};
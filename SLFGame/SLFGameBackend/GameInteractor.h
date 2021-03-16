#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class GameInteractor
{
public:
	~GameInteractor() = default;

	virtual void AddAnswers(const PlayerAnswers&) = 0;

	Event<AllAnswers> onAllAnswersReceived;
};
#pragma once
#include "DataTypes.h"

class TimerRessource
{
public:
	virtual			~TimerRessource() = default;

	virtual void	Start() = 0;
	virtual void	Stop() = 0;

	Event<> timeout;
};
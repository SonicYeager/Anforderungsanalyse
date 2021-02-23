#pragma once
#include "DataTypes.h"

class TimerRessource
{
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual ~TimerRessource() = default;

	Event<> timeout;
};
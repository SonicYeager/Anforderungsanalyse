#pragma once
#include "DataTypes.h"

class RandomGenRessource
{
public:
	virtual Letter GenerateLetter() = 0;
	virtual ~RandomGenRessource() = default; 
};
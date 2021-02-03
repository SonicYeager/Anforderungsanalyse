#pragma once
#include "DataTypes.h"

class RandomGenRessource
{
public:
	virtual Letter GenerateLetter(const Letters) = 0;
	virtual ~RandomGenRessource() = default; 
};
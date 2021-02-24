#pragma once
#include "DataTypes.h"

class RandomGenRessource
{
public:
	virtual Letter GenerateLetter() = 0;
	virtual Letter GenerateUnusedLetter(const Letters&) = 0;
	virtual ~RandomGenRessource() = default; 
};
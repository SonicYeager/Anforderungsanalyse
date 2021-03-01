#pragma once
#include "DataTypes.h"

class RandomGenRessource
{
public:
	virtual			~RandomGenRessource() = default; 

	virtual Letter	GenerateLetter() = 0;
	virtual Letter	GenerateUnusedLetter(const Letters&) = 0;
};
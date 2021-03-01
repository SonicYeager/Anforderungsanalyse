#pragma once
#include "framework.h"
#include "RandomGenRessource.h"

class /*[[deprecated("Use GenerateUnusedLetter instead")]]*/ RandomGenerator : public RandomGenRessource
{
public:
	Letter GenerateLetter		()					override;
	Letter GenerateUnusedLetter	(const Letters&)	override;
};


#pragma once
#include "framework.h"
#include "RandomGenRessource.h"

class LetterGenerator : public RandomGenRessource
{
public:
	Letter GenerateLetter() override;
};


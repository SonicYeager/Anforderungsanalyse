#pragma once
#include "framework.h"
#include "RandomGenRessource.h"

class RandomGenerator : public RandomGenRessource
{
public:
	Letter GenerateLetter() override;
	Letter GenerateLetterByFilter(const Letters&) override;
};


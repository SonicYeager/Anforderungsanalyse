#pragma once
#include "../SLFGameBackend/DataTypes.h"

class SLFParser
{
public:
	Categories ParseCategories(const std::string&);
	int ParseRoundCount(const std::string&);
};
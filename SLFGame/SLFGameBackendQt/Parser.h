#pragma once
#include "../SLFGameBackend/DataTypes.h"

class Parser
{
public:
	Categories ParseCategories(const std::string&);
	int ParseRoundCount(const std::string&);
};
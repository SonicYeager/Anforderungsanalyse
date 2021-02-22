#include "Parser.h"

Categories Parser::ParseCategories(const std::string& cats)
{
    return Categories();
}

int Parser::ParseRoundCount(const std::string& string)
{
	return std::stoi(string);
}

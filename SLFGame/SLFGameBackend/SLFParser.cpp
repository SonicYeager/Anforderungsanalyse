#pragma once
#include "SLFParser.h"

Categories SLFParser::ParseCategories(const std::string& cats)
{
	std::string delimiter = ",";
	Categories cat{};

	size_t last = 0;
	size_t next = 0; 
	while ((next = cats.find(delimiter, last)) != std::string::npos)
	{ 
		cat.push_back(cats.substr(last, next - last));
		last = next + 1; 
	} 
	cat.push_back(cats.substr(last));
    return cat;
}

int SLFParser::ParseRoundCount(const std::string& string)
{
	return std::stoi(string);
}

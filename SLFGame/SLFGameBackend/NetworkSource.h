#pragma once
#include <string>

class NetworkSource 
{
public:
	virtual std::string GenerateLobbyCode() = 0;
	virtual ~NetworkSource() = default;
};
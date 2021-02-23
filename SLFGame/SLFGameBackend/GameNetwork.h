#pragma once
#include "NetworkSource.h"

class GameNetwork : public NetworkSource
{
public:
	std::string GenerateLobbyCode() override;
};
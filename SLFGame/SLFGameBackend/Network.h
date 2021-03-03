#pragma once
#include "NetworkSource.h"

class Network : public NetworkSource
{
public:
	std::string GenerateLobbyCode() override;
};
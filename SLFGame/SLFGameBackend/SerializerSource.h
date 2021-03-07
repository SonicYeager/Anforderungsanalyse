#pragma once
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"
#include "Messages.h"

using namespace Messages;
class SerializerSource {
public:
	virtual std::vector<char> Serialize(const Message& msg) = 0;
	virtual Message Deserialize(const std::vector<char>& data) = 0;
};
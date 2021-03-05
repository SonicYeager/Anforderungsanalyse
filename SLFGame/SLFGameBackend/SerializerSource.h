#pragma once
#include "Messages.h"
#include "DataTypes.h"

class SerializerSource {
public:
	virtual void Serialize(Messages::Message msg, NetworkData data) = 0;
	virtual void Deserialize(Messages::Message msg, std::vector<char> data) = 0;
};
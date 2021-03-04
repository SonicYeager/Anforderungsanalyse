#pragma once
#include "DataTypes.h"
#include "SerializerSource.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class GameStatsSerializer : public SerializerSource
{
	void Serialize(Messages::Message msg, NetworkData data) override;
	void Deserialize(Messages::Message msg, std::vector<char> data) override;
	void Serialize_impl(Messages::HandleGameStats msg, NetworkData data);
	void Deserialize_impl(Messages::HandleGameStats msg, std::vector<char> data);
	void Serialize_impl(Messages::Alternative msg, NetworkData data);
	void Deserialize_impl(Messages::Alternative msg, std::vector<char> data);
};


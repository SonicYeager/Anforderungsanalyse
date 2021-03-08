#pragma once
#include "SerializerSource.h"

using namespace Messages;
using QDataStream = class QDataStream;

class GameStatsSerializer : public SerializerSource
{
public:
	std::vector<char> Serialize(const Message& msg) override;
	Message Deserialize(const std::vector<char>& data) override;
	void Serialize_impl(const HandleGameStats& msg, QDataStream& data);
	void Serialize_impl(const AddNewPlayer& msg, QDataStream& data);
	void Deserialize_impl(HandleGameStats& msg, QDataStream& data);
	void Deserialize_impl(AddNewPlayer& msg, QDataStream& data);
};
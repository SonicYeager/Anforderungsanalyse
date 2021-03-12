#pragma once
#include "SerializerSource.h"

using namespace Messages;
using QDataStream = class QDataStream;

class GameStatsSerializer : public SerializerSource
{
public:
	std::vector<char> Serialize(const Message& msg) override;
	Message Deserialize(const std::vector<char>& data) override;
	void Serialize_impl(const Playername& msg, QDataStream& data);
	void Deserialize_impl(Playername& msg, QDataStream& data);
	void Serialize_impl(const PlayerID& msg, QDataStream& data);
	void Deserialize_impl(PlayerID& msg, QDataStream& data);
	void Serialize_impl(const PlayerAnswers& msg, QDataStream& data);
	void Deserialize_impl(PlayerAnswers& msg, QDataStream& data);
	void Serialize_impl(const HandleGameSettings& msg, QDataStream& data);
	void Deserialize_impl(HandleGameSettings& msg, QDataStream& data);
	void Serialize_impl(const GameState& msg, QDataStream& data);
	void Deserialize_impl(GameState& msg, QDataStream& data);
	void Serialize_impl(const ChatMessage& msg, QDataStream& data);
	void Deserialize_impl(ChatMessage& msg, QDataStream& data);
	void Serialize_impl(const AllAnswers& msg, AllAnswers& data);
	void Deserialize_impl(AllAnswers& msg, AllAnswers& data);
};
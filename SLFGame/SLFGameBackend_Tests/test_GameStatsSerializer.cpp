#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsSerializer.h"

TEST(SerializerTest, SerializationAndDeserialization_AddNewPlayer)
{
	GameStatsSerializer serializer;
	AddNewPlayer msg;
	//AddNewPlayer result;

	msg.player.playerID = 5;
	msg.player.playerName = "Klausi";
	msg.player.points = 100;
	msg.player.answers = { "Mordor", "Mittelerde", "Mitheithel" };

	ByteStream data = serializer.Serialize(msg);
	Message result = serializer.Deserialize(data);
}
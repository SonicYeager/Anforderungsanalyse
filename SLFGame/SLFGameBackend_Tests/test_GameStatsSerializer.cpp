#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

TEST(SerializerTest, SerializationAndDeserialization_AddNewPlayer)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	AddNewPlayer result;
	AddNewPlayer msg;

	msg.player.playerName = "Klausi";
	msg.player.playerID = 5;
	msg.player.points = 100;
	msg.player.answers = { "Mordor", "Mittelerde", "Mitheithel" };

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onAddNewPlayer = [&result](const AddNewPlayer& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.player, result.player);
}

TEST(SerializerTest, SerializationAndDeserialization_HandleGameStats)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	HandleGameStats result;
	HandleGameStats msg;

	msg.gs.answers = { {"Mordor", "Mittelerde", "Mitheithel"}, {"Minas Morghul", "Mittelerde", "Maong Yi"} };
	msg.gs.categories = { "Stadt", "Land", "Fluss" };
	msg.gs.currentLetter = 'L';
	msg.gs.decisions = { {DECISION::SOLO} };
	msg.gs.maxRounds = 5;
	msg.gs.playerNames = { "Klausi", "Peter" };
	msg.gs.points = { 50, 100 };
	msg.gs.potentialId = 3;
	msg.gs.timeout = "jetzt";

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onHandleGameStats = [&result](const HandleGameStats& hgs) {result = hgs; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.gs, result.gs);
}

TEST(SerializerTest, SerializationAndDeserialization_Playername)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	Playername result;
	Playername msg;

	msg.playername = "Faust";

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onPlayername = [&result](const Playername& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.playername, result.playername);
}
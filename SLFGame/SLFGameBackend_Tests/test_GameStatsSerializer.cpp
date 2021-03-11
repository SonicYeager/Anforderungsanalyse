#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

//TEST(SerializerTest, SerializationAndDeserialization_HandleGameStats)
//{
//	GameStatsSerializer serializer;
//	MessageHandler msgHandler;
//
//	Message resultingMsg;
//	HandleGameStats result;
//	HandleGameStats msg;
//
//	msg.gs.answers = { {"Mordor", "Mittelerde", "Mitheithel"}, {"Minas Morghul", "Mittelerde", "Maong Yi"} };
//	msg.gs.categories = { "Stadt", "Land", "Fluss" };
//	msg.gs.currentLetter = 'L';
//	msg.gs.decisions = { {DECISION::SOLO} };
//	msg.gs.maxRounds = 5;
//	msg.gs.playerNames = { "Klausi", "Peter" };
//	msg.gs.points = { 50, 100 };
//	msg.gs.timeout = "jetzt";
//	msg.gs.state = STATE::LOBBY;
//
//	ByteStream data = serializer.Serialize(msg);
//	resultingMsg = serializer.Deserialize(data);
//
//	msgHandler.onHandleGameStats = [&result](const HandleGameStats& hgs) {result = hgs; };
//	msgHandler.handleMessage(resultingMsg);
//
//	EXPECT_EQ(msg.gs, result.gs);
//}

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

TEST(SerializerTest, SerializationAndDeserialization_PlayerID)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	PlayerID result;
	PlayerID msg;

	msg.id = 6;

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onPlayerID = [&result](const PlayerID& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.id, result.id);
}

TEST(SerializerTest, SerializationAndDeserialization_PlayerAnswers)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	PlayerAnswers result;
	PlayerAnswers msg;

	msg.answers = { "Helms Klamm", "Hagsend" "Hurin der Lange" };

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onPlayerAnswers = [&result](const PlayerAnswers& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.answers, result.answers);
}
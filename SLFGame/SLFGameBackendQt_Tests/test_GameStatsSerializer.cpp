#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

inline bool operator==(const RoundData& left, const RoundData& right)
{
	return left.roundTime == right.roundTime &&
		left.categories == right.categories &&
		left.letter == right.letter &&
		left.maxRounds == right.maxRounds  &&
		left.currentRound == right.currentRound &&
		left.points == right.points;
}

inline bool operator==(const LobbySettings& left, const LobbySettings& right)
{
	return left.timeout == right.timeout &&
		left.categories == right.categories &&
		left.playerNames == right.playerNames &&
		left.rounds == right.rounds;
}

inline bool operator==(const Index& left, const Index& right)
{
	return left.answerIDX == right.answerIDX &&
		left.categoryIDX == right.categoryIDX &&
		left.voterIDX == right.voterIDX;
}

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

TEST(SerializerTest, SerializationAndDeserialization_RoundSetup)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	RoundSetup result;
	RoundSetup msg;

	msg.data = { {"Stadt", "Land" "Fluss" }, "C", "bis Stop", 0, 5, 10};

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onRoundSetup = [&result](const RoundSetup& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.data, result.data);
}

TEST(SerializerTest, SerializationAndDeserialization_AllAnswers)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	AllAnswers result;
	AllAnswers msg;

	msg.ans = { {"Jackpot", "Fortune", "Ace"} };

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onAllAnswers = [&result](const AllAnswers& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.ans, result.ans);
}

TEST(SerializerTest, SerializationAndDeserialization_ChatMsg)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	ChatMessage result;
	ChatMessage msg;

	msg.sender = "HanSolo";
	msg.text = "Blast'em all";

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onChatMessage = [&result](const ChatMessage& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.sender, result.sender);
	EXPECT_EQ(msg.text, result.text);
}

TEST(SerializerTest, SerializationAndDeserialization_GameState)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	GameState result;
	GameState msg;

	msg.state = STATE::MAINMENU;

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onGameState = [&result](const GameState& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.state, result.state);
}

TEST(SerializerTest, SerializationAndDeserialization_HandleGameSettings)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	HandleGameSettings result;
	HandleGameSettings msg;

	std::string categories{};
	std::string timeout{};
	std::string rounds{};
	std::map<int, std::string> playerNames{};

	msg.ls = { "Stadt,Land,Fluss", "bis Stop", "10", {{0, "IAMGROOT"}} };

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onHandleGameSettings = [&result](const HandleGameSettings& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.ls, result.ls);
}

TEST(SerializerTest, SerializationAndDeserialization_AnswerIndex)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	AnswerIndex result;
	AnswerIndex msg;

	msg.index.answerIDX = 1;
	msg.index.categoryIDX = 2;
	msg.index.voterIDX = 3;

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onAnswerIndex = [&result](const AnswerIndex& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.index, result.index);
}

TEST(SerializerTest, SerializationAndDeserialization_FinalScores)
{
	GameStatsSerializer serializer;
	MessageHandler msgHandler;

	Message resultingMsg;
	FinalScores result;
	FinalScores msg;

	msg.scores = { {0, 120}, {1, 60} };

	ByteStream data = serializer.Serialize(msg);
	resultingMsg = serializer.Deserialize(data);

	msgHandler.onFinalScores = [&result](const FinalScores& anp) {result = anp; };
	msgHandler.handleMessage(resultingMsg);

	EXPECT_EQ(msg.scores, result.scores);
}
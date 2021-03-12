#include "MessageHandler.h"

void MessageHandler::handleMessage(const Message& msg)
{
	std::visit([&](auto&& type) {on(type); }, msg);
}

void MessageHandler::on(const PlayerAnswers& msg)
{
	onPlayerAnswers(msg);
}

void MessageHandler::on(const HandleGameSettings& msg)
{
	onHandleGameSettings(msg);
}

void MessageHandler::on(const GameState& msg)
{
	onGameState(msg);
}

void MessageHandler::on(const ChatMessage& msg)
{
	onChatMessage(msg);
}

void MessageHandler::on(const Playername& msg)
{
	onPlayername(msg);
}

void MessageHandler::on(const PlayerID& msg)
{
	onPlayerID(msg);
}

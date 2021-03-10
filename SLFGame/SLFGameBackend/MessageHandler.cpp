#include "MessageHandler.h"

void MessageHandler::handleMessage(const Message& msg)
{
	std::visit([&](auto&& type) {on(type); }, msg);
}

void MessageHandler::on(const HandleGameStats& msg)
{
	onHandleGameStats(msg);
}

void MessageHandler::on(const PlayerAnswers& msg)
{
	onPlayerAnswers(msg);
}

void MessageHandler::on(const HandleGameSettings& msg)
{
	onHandleGameSettings(msg);
}

void MessageHandler::on(const Playername& msg)
{
	onPlayername(msg);
}

void MessageHandler::on(const PlayerID& msg)
{
	onPlayerID(msg);
}

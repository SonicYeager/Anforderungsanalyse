#include "MessageHandler.h"

void MessageHandler::handleMessage(const Message& msg)
{
	std::visit([&](auto&& type) {on(type); }, msg);
}

void MessageHandler::on(const HandleGameStats& msg)
{
	onHandleGameStats(msg);
}

void MessageHandler::on(const AddNewPlayer& msg)
{
	onAddNewPlayer(msg);
}

void MessageHandler::on(const Playername& msg)
{
	onPlayername(msg);
}

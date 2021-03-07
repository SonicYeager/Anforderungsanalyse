#include "NetworkHandler.h"

void NetworkHandler::handleMessage(const Message& msg)
{
	std::visit([&](auto&& type) {on(type); }, msg);
}

void NetworkHandler::on(const HandleGameStats& msg)
{
	onHandleGameStats(msg);
}

void NetworkHandler::on(const AddNewPlayer& msg)
{
	onAddNewPlayer(msg);
}

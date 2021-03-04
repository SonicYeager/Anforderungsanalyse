#include "NetworkHandler.h"

void MessageHandler::handleMessage(Messages::Message msg, NetworkData data)
{
	std::visit([&](auto&& type) {on(type, data); }, msg);
}

void MessageHandler::on(Messages::HandleGameStats pl, NetworkData data)
{
	onGet(pl, data);
}

void MessageHandler::on(Messages::Alternative pl, NetworkData data)
{
	onSet(pl, data);
}

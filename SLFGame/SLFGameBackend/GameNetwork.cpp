#include "GameNetwork.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

std::string GameNetwork::GenerateLobbyCode()
{
	QHostInfo info{};
	auto addresses = info.addresses();
    return addresses.at(0).toString().toStdString();
}

#include "GameNetwork.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

std::string GameNetwork::GenerateLobbyCode()
{
	//QHostAddress& addr = QHostAddress(QHostAddress::AnyIPv4);
	const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress& address : QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
			return address.toString().toStdString();
	}
}

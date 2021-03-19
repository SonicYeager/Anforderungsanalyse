#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class ServerInteractor
{
public:
	virtual ~ServerInteractor() = default;

	virtual void StartServer() = 0;
	virtual void Broadcast(const Message&) = 0;
	virtual void WriteTo(int, const Message&) = 0;

	//Event<const std::string> onLog;

	//game inter
	Event<int> onRemovePlayer;
	Event<int, std::vector<std::string>> onAddAnswers;
	Event<int, std::string> onAddPlayer;
	Event<LobbySettings> onSetGameSettings;
	Event<STATE> onChangeGameState;
	Event<LobbyCode> onSetLobbyCode;
	Event<Index> onAnswerIndex;
};
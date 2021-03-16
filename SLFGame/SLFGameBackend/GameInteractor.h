#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class GameInteractor
{
public:
	~GameInteractor() = default;
	//ui client
	virtual void HostLobby(const std::string&) = 0;
	virtual void JoinLobby(const LobbyCode&, const std::string&) = 0;
	virtual void LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds) = 0;
	virtual void ChatMessageReceived(const std::string& sender, const std::string& text) = 0;
	virtual void StateChangeTriggered(const STATE&) = 0;
	virtual void AnswersReceived(const std::vector<std::string>&) = 0;

	//server
	virtual void RemovePlayer(const int&) = 0;
	virtual void AddAnswers(int, const std::vector<std::string>&) = 0;
	virtual void AddPlayer(int, const PlayerStats&) = 0;
	virtual void SetGameSettings(const LobbySettings&) = 0;
	virtual void ChangeGameState(const STATE&) = 0;
	virtual void SetLobbyCode(const LobbyCode&) = 0;

	//ui events
	Event<int> onReceivedID;
	Event<LobbyCode> onSetLobbyCode;
	Event<LobbySettings> onUpdateLobbySettings;
	Event<STATE> onGameState;
	Event<ChatMessage> onChatMessage;
	Event<std::vector<std::vector<std::string>>> onAllAnswers;
	Event<RoundData> onRoundData;

};
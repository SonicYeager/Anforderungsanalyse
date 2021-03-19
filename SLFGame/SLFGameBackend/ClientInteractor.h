#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class ClientInteractor
{
public:
	// delete > virtual void EndRound(const std::vector<DECISION>& decisions) = 0;
	virtual void HostLobby(const std::string&) = 0;
	virtual void JoinLobby(const LobbyCode&, const std::string&) = 0;
	virtual void LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds) = 0;
	virtual void ChatMessageReceived(const std::string& sender, const std::string& text) = 0;
	virtual void StateChangeTriggered(const STATE&) = 0;
	virtual void AnswersReceived(const std::vector<std::string>&) = 0;
	virtual void ChangeVoteStateTriggered(int, int, int) = 0;
	virtual ~ClientInteractor() = default;

	//ui events
	Event<int> onReceivedID;
	Event<LobbyCode> onSetLobbyCode;
	Event<LobbySettings> onUpdateLobbySettings;
	Event<STATE> onGameState;
	Event<ChatMessage> onChatMessage;
	Event<std::vector<std::vector<std::string>>> onAllAnswers;
	Event<RoundData> onRoundData;
	Event<Index> onVoteChange;

	//server events
	Event<> onStartServer;
};
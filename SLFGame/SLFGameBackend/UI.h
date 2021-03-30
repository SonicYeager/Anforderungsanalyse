#pragma once
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

class UI
{
public:
    virtual void ReceiveID(int) = 0;
    virtual void UpdateLobby(const LobbySettings&) = 0;
    virtual void SetLobbyCode(const LobbyCode&) = 0;
    virtual void UpdateGameState(const STATE&) = 0;
    virtual void ChatMessageReceived(const ChatMessage&) = 0;
    virtual void ReveiveAllAnswers(const std::vector<std::vector<std::string>> &) = 0;
    virtual void ReceiveRoundData(const RoundData&) = 0;
    virtual void ReceiveVoteChange(const Index&) = 0;
    virtual void ReceiveFinalScores(const Scores&) = 0;
    virtual void PlayerLeft(int) = 0;
	virtual ~UI() = default;

	Event<const std::string&> onHostLobby;
	Event<const std::string&, const std::string&> onJoinLobby;
    Event<const std::string&, const std::string&, const std::string&> onLobbySettingsChanged;
    Event<const std::string&, const std::string&> onChatMessage;
    Event<const std::vector<std::string>&>  onSendAnswers;
    Event<const STATE&> onState;
    Event<int, int, int> onChangeVoteState;
    Event<> onDisconnect;
};

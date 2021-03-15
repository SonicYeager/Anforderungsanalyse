#pragma once
#include "framework.h"
#include "ClientInteractor.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "ClientSource.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"

class ClientInteractorImpl : public ClientInteractor
{
public:
	explicit ClientInteractorImpl(RandomGenRessource*, ClientSource*, SerializerSource*, MessageHandlerLogic*);
	void HostLobby(const std::string&) override;
	void JoinLobby(const LobbyCode&, const std::string&) override;
	void LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds) override;
	void ChatMessageReceived(const std::string& sender, const std::string& text) override;
	void StateChangeTriggered(const STATE&) override;
	void AnswersReceived(const std::vector<std::string>&) override;
	// delete > void EndRound(const std::vector<DECISION>&) override;
	//			GameStats m_GameStats;

	//msg events
	void OnMsgID(const PlayerID&);
	void OnMsgHandleGameSettings(const HandleGameSettings&);
	void OnMsgGameState(const GameState&);
	void OnChatMessage(const ChatMessage&);
	void OnAllAnswers(const AllAnswers&);
	void OnRoundSetup(const RoundSetup&);

private:
	//client events
	void OnDataReceived(const ByteStream&);

	ClientSource* m_pClient;
	MessageHandlerLogic* m_pMsgHandler;
	SerializerSource* m_pSerializer;
	RandomGenRessource* m_pRandomGenerator;

	// Geerbt über ClientInteractor
};


#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* u, GameInteractor* gi,
                       ClientInteractor* ci,
                       ServerInteractor* si) :
    m_pUi(u),
    m_pGameInter(gi),
    m_pClientInter(ci),
    m_pServerInter(si)
{

    m_pClientInter->onStartServer = [this] {	m_pServerInter->StartServer(); };

    //UI EVENTS

    //m_pUi->onPrepareNextRound           = [this](std::vector<DECISION> decisions)
    //                                      {m_pClientInter->EndRound(decisions);};

    m_pUi->onHostLobby                  = [this](const std::string& playerName)
                                            {m_pClientInter->HostLobby(playerName);};

    m_pUi->onJoinLobby                  = [this](const std::string& lobbyCode, const std::string& playerName)
                                            {m_pClientInter->JoinLobby(lobbyCode, playerName);};

    m_pUi->onLobbySettingsChanged       = [this](const std::string& customCats,const std::string& timeLeft,const std::string& maxRounds)
                                            {m_pClientInter->LobbyChanged(customCats, timeLeft, maxRounds);};

    m_pUi->onChatMessage                = [this](const std::string& sender, const std::string& text)
                                            {m_pClientInter->ChatMessageReceived(sender,text);};

    m_pUi->onState                      = [this](const STATE& state)
                                            {m_pClientInter->StateChangeTriggered(state);};

    m_pUi->onSendAnswers                = [this](const std::vector<std::string> answers)
                                            {m_pClientInter->AnswersReceived(answers);};

    //CLIENT EVENTS

    m_pClientInter->onReceivedID            = [this](int id)
                                                {m_pUi->ReceiveID(id);};

    m_pClientInter->onUpdateLobbySettings   = [this](LobbySettings ls)
                                                {m_pUi->UpdateLobby(ls);};

    m_pClientInter->onSetLobbyCode          = [this](LobbyCode lobbyCode)
                                                {m_pUi->SetLobbyCode(lobbyCode);};

    m_pClientInter->onGameState             = [this](STATE state)
                                                {m_pUi->UpdateGameState(state);};

    m_pClientInter->onChatMessage           = [this](ChatMessage cm)
                                                {m_pUi->ChatMessageReceived(cm);};

    m_pClientInter->onAllAnswers            = [this](std::vector<std::vector<std::string>> answers)
                                                {m_pUi->ReveiveAllAnswers(answers);};

    m_pClientInter->onRoundData             = [this](const RoundData& data)
                                                {m_pUi->ReceiveRoundData(data);};
}

int Controller::Run(int argc, char *argv[], QObject& obj)
{
    return 0;
}

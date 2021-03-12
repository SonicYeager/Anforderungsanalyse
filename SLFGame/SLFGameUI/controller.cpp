#include "controller.h"
#include "DataTypes.h"

Controller::Controller(UI* ui, ClientInteractor* clientInter, ServerInteractor* serverInter) :
    m_pUi(ui),
    m_pServerInter(serverInter),
    m_pClientInter(clientInter)
{
    //connect ui + inter

    m_pUi->onPrepareNextRound           = [this](std::vector<DECISION> decisions)
                                          {m_pClientInter->EndRound(decisions);};

    m_pUi->onHostLobby                  = [this](const std::string& playerName)
                                          {m_pClientInter->HostLobby(playerName);};

    m_pUi->onJoinLobby                  = [this](const std::string& lobbyCode, const std::string& playerName)
                                          {m_pClientInter->JoinLobby(lobbyCode, playerName);};

    m_pUi->onLobbySettingsChanged       = [this](const std::string& customCats,const std::string& timeLeft,const std::string& maxRounds)
                                          {m_pClientInter->LobbyChanged(customCats, timeLeft, maxRounds);};
    m_pUi->onChatMessage                = [this](const std::string& sender, const std::string& text)
                                          {m_pClientInter->ChatMessageReceived(sender,text);};

    m_pClientInter->onReceivedID        = [this](int id)
                                          {m_pUi->ReceiveID(id);};

    m_pClientInter->onUpdateLobbySettings  = [this](LobbySettings ls)
                                          {m_pUi->UpdateLobby(ls);};

    m_pClientInter->onStartServer       = [this]()
                                          {m_pServerInter->StartServer();};

    m_pClientInter->onSetLobbyCode      = [this](LobbyCode lobbyCode)
                                          {m_pUi->SetLobbyCode(lobbyCode);};

    m_pClientInter->onGameState         = [this](STATE state)
                                          {m_pUi->UpdateGameState(state);};
    m_pClientInter->onChatMessage       = [this](ChatMessage cm)
                                          {m_pUi->ChatMessageReceived(cm);};

}

void Controller::Run()
{
    //init here
}

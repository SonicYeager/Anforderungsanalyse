#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{}

// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::ReceiveID(int id)
{
    setPlayerId(id);
}

void QmlAdapter::UpdateLobby(const LobbySettings & ls)
{
    //setCustomCategories(ls.categories.c_str());
    //setRoundTime(ls.timeout.c_str());
    //setMaxRounds(ls.rounds.c_str());
    _customCategories = ls.categories.c_str();
    _maxRounds = ls.rounds.c_str();
    _roundTime = ls.timeout.c_str();
    _players.clear();
    _players = ls.playerNames;
    setPlayerCount(_players.size());
    emit playerCountChanged();
    emit playersChanged();
    emit customCategoriesChanged();
    emit maxRoundsChanged();
    emit roundTimeChanged();
}

void QmlAdapter::SetLobbyCode(const LobbyCode & lobbycode)
{
    setLobbyCode(lobbycode.c_str());
}

void QmlAdapter::UpdateGameState(const STATE & state)
{
    setView(GetViewFromState(state));
}

void QmlAdapter::ChatMessageReceived(const ChatMessage & cm)
{
    AddChatMessage(cm.sender.c_str(), cm.text.c_str());
}

// ------------------------------------------ getter ------------------------------------------
#define getterFunctions {

QString QmlAdapter::getLetter()
{
    return _letter;
}

QString QmlAdapter::getLobbyCode()
{
    return _lobbyCode;
}

QString QmlAdapter::getCustomCategories()
{
    return _customCategories;
}

StrVector QmlAdapter::getCategories()
{
    return _categories;
}

StrVector2D QmlAdapter::getAnswers()
{
    return _answers;
}

QList<QVariantMap> QmlAdapter::getPlayers()
{
   QList<QVariantMap> res{};
   for(const auto& player : _players)
       res.append(QVariantMap({{"id", QVariant(player.first)}, {"name", QVariant(QString(player.second.c_str()))}}));
    return res;
}

bool QmlAdapter::getCustomChecked()
{
    return _customChecked;
}

int QmlAdapter::getCategoryCount()
{
    return _categoryCount;
}

int QmlAdapter::getCurrentRound()
{
    return _currentRound;
}

QString QmlAdapter::getMaxRounds()
{
    return _maxRounds;
}

QString QmlAdapter::getRoundTime()
{
    return _roundTime;
}

int QmlAdapter::getPoints()
{
    return _points;
}

int QmlAdapter::getActiveOverviewItem()
{
    return _activeOverviewItem;
}

int QmlAdapter::getPlayerCount()
{
    return _playerCount;
}

int QmlAdapter::getPlayerId()
{
    return _playerId;
}

QString QmlAdapter::getTimeLeft()
{
    return _timeLeft;
}

QString QmlAdapter::getView()
{
    return _view;
}

QString QmlAdapter::getPlayerName()
{
    return _playerName;
}

QString QmlAdapter::getChatLog()
{
    return _chatLog;
}

#define getterFunctionsEnd }
// ------------------------------------------ setter ------------------------------------------
#define setterFuntions {

void QmlAdapter::setLetter(QString letter)
{
    if (letter == _letter)
        return;
    _letter = letter;
    emit letterChanged();
}

void QmlAdapter::setLobbyCode(QString lobbyCode)
{
    if (lobbyCode == _lobbyCode)
        return;
    _lobbyCode = lobbyCode;
    emit lobbyCodeChanged();
}

void QmlAdapter::setCustomCategories(QString customCategories)
{
    if (customCategories == _customCategories)
        return;
    _customCategories = customCategories;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit customCategoriesChanged();
}

void QmlAdapter::setRoundTime(QString roundTime)
{
    if (roundTime == _roundTime)
        return;
    _roundTime = roundTime;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit roundTimeChanged();
}

void QmlAdapter::setCategories(StrVector categories)
{
    if (categories == _categories)
        return;
    _categories = categories;
    _categoryCount = _categories.size();
    emit categoriesChanged();
    emit categoryCountChanged();
}

void QmlAdapter::setAnswers(StrVector2D answers)
{
    if (answers == _answers)
        return;
    _answers = answers;
    _decisions.clear();
    for (int i = 0; i < _playerCount; i++)
        _decisions.emplace_back();
    for (int i = 0; i < _categoryCount - 1; i++)
        _decisions[i].emplace_back(DECISION::UNANSWERED);

    emit answersChanged();
    emit decisionsChanged();
}

void QmlAdapter::setPlayers(QList<QVariantMap> players)
{
    PlayerMap res{};
    for(const auto& player : players)
        res.emplace(player["id"].toInt(), player["name"].toString().toStdString());
    if (res == _players)
        return;
    _players = res;
    emit playersChanged();
}

void QmlAdapter::setCustomChecked(bool checked)
{
    if (checked == _customChecked)
        return;
    _customChecked = checked;
    emit customCheckedChanged();
}

void QmlAdapter::setCategoryCount(int categoryCount)
{
    if (categoryCount == _categoryCount)
        return;
    _categoryCount = categoryCount;
    emit categoryCountChanged();
}

void QmlAdapter::setCurrentRound(int currentRound)
{
    if (currentRound == _currentRound)
        return;
    _currentRound = currentRound;
    emit currentRoundChanged();
}

void QmlAdapter::setMaxRounds(QString maxRounds)
{
    if (maxRounds == _maxRounds)
        return;
    _maxRounds = maxRounds;
    if(_playerId == 0)
        lobbySettingsChanged();
    emit maxRoundsChanged();
}

void QmlAdapter::setView(QString view)
{
    if (view == _view)
        return;
    _view = view;
    emit viewChanged();
}

void QmlAdapter::setPlayerName(QString playerName)
{
    if (playerName == _playerName)
        return;
    _playerName = playerName;
    emit playerNameChanged();
}

void QmlAdapter::setPoints(int points)
{
    if (points == _points)
        return;
    _points = points;
    emit pointsChanged();
}

void QmlAdapter::setActiveOverviewItem(int activeOverviewItem)
{
    if (activeOverviewItem == _activeOverviewItem)
        return;
    _activeOverviewItem = activeOverviewItem;
    emit activeOverviewItemChanged();
}

void QmlAdapter::setPlayerCount(int playerCount)
{
    if (playerCount == _playerCount)
        return;
    _playerCount = playerCount;
    emit playerCountChanged();
}

void QmlAdapter::setPlayerId(int playerId)
{
    if (playerId == _playerId)
        return;
    _playerId = playerId;
    emit playerIdChanged();
}

void QmlAdapter::setTimeLeft(QString timeLeft)
{
    if (timeLeft == _timeLeft)
        return;
    _timeLeft = timeLeft;
    emit timeLeftChanged();
}

#define slotFunctionsEnd }
// ------------------------------------------ slots ------------------------------------------
#define slotFunctions {

QString QmlAdapter::getCategoryName(int idx)
{
    return QString::fromUtf8(_categories[idx].c_str());
}

QString QmlAdapter::getAnswer(int playerID, int categoryIDX)
{
    return QString::fromUtf8(_answers[playerID][categoryIDX].c_str());
}

QString QmlAdapter::getPlayer(int idx)
{
    return QString::fromUtf8(_players[idx].c_str());
}

DECISION QmlAdapter::getDecision(int playerID, int categoryIDX)
{
    return _decisions[playerID][categoryIDX];
}

void QmlAdapter::setActiveItemIA(int idx)
{
    setActiveOverviewItem(idx);
}

void QmlAdapter::setDecision(int playerID, int categoryIDX, int newVal)
{
    auto dec = static_cast<DECISION>(newVal);
    _decisions[playerID][categoryIDX] = dec;
    emit decisionsChanged();
}

void QmlAdapter::prepareGame()
{
    onPrepareGame(_customCategories.toStdString(), _timeLeft.toStdString(), _maxRounds.toStdString());
}

void QmlAdapter::prepareOverview()
{
    onPrepareOverview(_unhandledanswers);
}

void QmlAdapter::prepareNextRound()
{
    // CHANGE ME SOON ----------------------------------------------------------------------
    onPrepareNextRound(_decisions[0]);
}

void QmlAdapter::addAnswer(QString answer)
{
    _unhandledanswers.emplace_back(answer.toStdString());
}

void QmlAdapter::addPlayerAnswers(GameStats gs)
{
    StrVector2D result;
    for (unsigned long long i = 0; i < gs.players.size(); i++)
           result.push_back(gs.players[i].answers);
    setAnswers(result);
}

void QmlAdapter::hostLobby()
{
    onHostLobby(_playerName.toStdString());
}

void QmlAdapter::joinLobby()
{
    onJoinLobby(_lobbyCode.toStdString(), _playerName.toStdString());
}

void QmlAdapter::lobbySettingsChanged()
{
    onLobbySettingsChanged(_customCategories.toStdString(), _roundTime.toStdString(), _maxRounds.toStdString());
}

void QmlAdapter::sendChatMessage(QString str)
{
    onChatMessage(_playerName.toStdString(), str.toStdString());
}

QString QmlAdapter::GetViewFromState(STATE view)
{
    switch (view)
    {
        case STATE::MAINMENU :      return "MainMenu";
        case STATE::LOBBY :         return "Lobby";
        case STATE::INGAME :        return "Input";
        case STATE::OVERVIEW :      return "Overview";
        case STATE::INTERVENTION :  return (getPlayerId() == 0) ? "Intervention" : "Waiting";
        case STATE::FINALSCORES :   return "FinalScores"; break;
    }
}

void QmlAdapter::AddChatMessage(const QString &sender, const QString &text)
{
    QString output = (sender == _playerName) ? "Du" : sender;
    _chatLog += output + ": " + text + "\n";
    emit chatLogChanged();
}

#define slotFunctionsEnd }

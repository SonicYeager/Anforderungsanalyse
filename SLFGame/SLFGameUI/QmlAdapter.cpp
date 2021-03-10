#include "QmlAdapter.h"

QmlAdapter::QmlAdapter(QObject *parent) :
    QObject(parent)
{}

// ------------------------------------------ initializer function ------------------------------------------

void QmlAdapter::ReceiveID(int id)
{
    setPlayerId(id);
}

void QmlAdapter::PrepareGame(const GameStats & gs)
{
    _unhandledanswers = {};
    setCurrentRound(gs.currentRound);
    setLetter(QChar(gs.currentLetter));
    setCategories(gs.categories);
    setPoints(gs.players[_playerId].points);
    setView(STATE::INGAME);
}

void QmlAdapter::PrepareFinalScores(const GameStats & gs)
{
    setPoints(gs.players[_playerId].points);
    setView(STATE::FINALSCORES);
}

void QmlAdapter::PrepareOverview(const GameStats & gs)
{
    addPlayerAnswers(gs);
    setView(STATE::OVERVIEW);
    emit answersChanged();
}

void QmlAdapter::PrepareLobby(const GameStats & gs)
{
    setLobbyCode(QString::fromLocal8Bit(gs.lobbyCode.c_str()));
    _players.clear();
    for(unsigned long long i{}; i < gs.players.size(); ++i)
        _players.push_back(gs.players[i].playerName);
    setPlayerCount(_players.size());
    setTimeLeft(gs.timeout.c_str());
    emit playerCountChanged();
    emit playersChanged();
    setView(gs.state);
}

void QmlAdapter::UpdateGameStats(const GameStats& gs)
{
    _players.clear();
    for(unsigned long long i{}; i < gs.players.size(); ++i)
        _players.push_back(gs.players[i].playerName);
    setPlayerCount(_players.size());
    setMaxRounds(QString::number(gs.maxRounds));
    setTimeLeft(gs.timeout.c_str());
    emit playerCountChanged();
    emit playersChanged();
    setView(gs.state);
}

void QmlAdapter::UpdateLobby(const LobbySettings & ls)
{
    setMaxRounds(ls.rounds.c_str());
    setTimeLeft(ls.timeout.c_str());
    setCustomCategories(ls.categories.c_str());
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

StrVector QmlAdapter::getPlayers()
{
    return _players;
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
    if (getPlayerId() == 0)
        LobbySettingsChanged();
    emit customCategoriesChanged();
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

void QmlAdapter::setPlayers(StrVector players)
{
    if (players == _players)
        return;
    _players = players;
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
    if (getPlayerId() == 0)
        LobbySettingsChanged();
    emit maxRoundsChanged();
}

void QmlAdapter::setView(STATE view)
{
    QString newView;
    switch (view)
    {
        case STATE::MAINMENU :      newView = "MainMenu"; break;
        case STATE::LOBBY :         newView = "Lobby"; break;
        case STATE::INGAME :        newView = "Input"; break;
        case STATE::OVERVIEW :      newView = "Overview"; break;
        case STATE::INTERVENTION :  newView = (getPlayerId() == 0) ? "Intervention" : "Waiting"; break;
        case STATE::FINALSCORES :   newView = "FinalScores"; break;
    }

    if (newView == _view)
        return;
    _view = newView;
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
    _playerId = playerId;
}

void QmlAdapter::setTimeLeft(QString timeLeft)
{
    if (timeLeft == _timeLeft)
        return;
    _timeLeft = timeLeft;
    if (getPlayerId() == 0 && _view == "Lobby")
        LobbySettingsChanged();
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

void QmlAdapter::LobbySettingsChanged()
{
    onLobbySettingsChanged(_customCategories.toStdString(), _timeLeft.toStdString(), _maxRounds.toStdString());
}

#define slotFunctionsEnd }

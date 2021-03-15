#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#endif // QMLADAPTER_H
#include <QObject>
#include <vector>
#include <string>
#include <QAbstractListModel>
#include "UI.h"

using StrVector = std::vector<std::string>;
using PlayerMap = std::map<int, std::string>;
using StrVector2D = std::vector<StrVector>;
using DecVector = std::vector<DECISION>;
using DecVector2D = std::vector<DecVector>;
class QmlAdapter : public QObject, public UI
{
    Q_OBJECT
    Q_PROPERTY(QString letter              READ getLetter                WRITE setLetter                NOTIFY letterChanged)
    Q_PROPERTY(QString lobbyCode           READ getLobbyCode             WRITE setLobbyCode             NOTIFY lobbyCodeChanged)
    Q_PROPERTY(QString customCategories    READ getCustomCategories      WRITE setCustomCategories      NOTIFY customCategoriesChanged)
    Q_PROPERTY(QString maxRounds           READ getMaxRounds             WRITE setMaxRounds             NOTIFY maxRoundsChanged)
    Q_PROPERTY(QString roundTime           READ getRoundTime             WRITE setRoundTime             NOTIFY roundTimeChanged)
    Q_PROPERTY(QString timeLeft            READ getTimeLeft              WRITE setTimeLeft              NOTIFY timeLeftChanged)
    Q_PROPERTY(QString view                READ getView                  WRITE setView                  NOTIFY viewChanged)
    Q_PROPERTY(QString playerName          READ getPlayerName            WRITE setPlayerName            NOTIFY playerNameChanged)
    Q_PROPERTY(QString chatLog             READ getChatLog               NOTIFY chatLogChanged)
    Q_PROPERTY(StrVector categories        READ getCategories            WRITE setCategories            NOTIFY categoriesChanged)
    Q_PROPERTY(StrVector2D answers         READ getAnswers               WRITE setAnswers               NOTIFY answersChanged)
    Q_PROPERTY(QList<QVariantMap> players  READ getPlayers               WRITE setPlayers               NOTIFY playersChanged)
    Q_PROPERTY(int categoryCount           READ getCategoryCount         WRITE setCategoryCount         NOTIFY categoryCountChanged)
    Q_PROPERTY(int currentRound            READ getCurrentRound          WRITE setCurrentRound          NOTIFY currentRoundChanged)
    Q_PROPERTY(int points                  READ getPoints                WRITE setPoints                NOTIFY pointsChanged)
    Q_PROPERTY(int activeOverviewItem      READ getActiveOverviewItem    WRITE setActiveOverviewItem    NOTIFY activeOverviewItemChanged)
    Q_PROPERTY(int playerCount             READ getPlayerCount           WRITE setPlayerCount           NOTIFY playerCountChanged)
    Q_PROPERTY(int playerId                READ getPlayerId              WRITE setPlayerId              NOTIFY playerIdChanged)
    Q_PROPERTY(bool customChecked          READ getCustomChecked         WRITE setCustomChecked         NOTIFY customCheckedChanged)


public:
    explicit QmlAdapter         (QObject *parent = nullptr);

    void ReceiveID              (int)              override;
    void UpdateLobby            (const LobbySettings&) override;
    void SetLobbyCode           (const LobbyCode&) override;
    void UpdateGameState        (const STATE&) override;
    void ChatMessageReceived    (const ChatMessage&) override;
    void ReveiveAllAnswers      (const std::vector<std::vector<std::string>> &) override;
    void ReceiveRoundData       (const RoundData&) override;

    QString getLetter();
    QString getLobbyCode();
    QString getCustomCategories();
    QString getMaxRounds();
    QString getRoundTime();
    QString getTimeLeft();
    QString getView();
    QString getPlayerName();
    QString getChatLog();
    StrVector getCategories();
    StrVector2D getAnswers();
    QList<QVariantMap> getPlayers();
    int getCategoryCount();
    int getCurrentRound();
    int getPoints();
    int getActiveOverviewItem();
    int getPlayerCount();
    int getPlayerId();
    bool getCustomChecked();


    void setLetter                      (QString letter);
    void setLobbyCode                   (QString lobbyCode);
    void setCustomCategories            (QString customCategories);
    void setRoundTime                   (QString customCategories);
    void setTimeLeft                    (QString timeLeft);
    void setMaxRounds                   (QString maxRounds);
    void setView                        (QString view);
    void setPlayerName                  (QString playerName);
    void setCategories                  (StrVector categories);
    void setAnswers                     (StrVector2D answers);
    void setPlayers                     (QList<QVariantMap> players);
    void setCategoryCount               (int categoryCount);
    void setCurrentRound                (int currentRound);
    void setPoints                      (int points);
    void setActiveOverviewItem          (int activeOverviewItem);
    void setPlayerCount                 (int playerCount);
    void setPlayerId                    (int playerId);
    void setCustomChecked               (bool checked);

public slots:

    QString getCategoryName(int idx);
    QString getAnswer(int playerID, int categoryIDX);
    QString getPlayer(int idx);
    DECISION getDecision(int playerID, int categoryIDX);
    void setActiveItemIA(int idx);
    void setDecision(int playerID, int categoryIDX, int newVal);
    void prepareGame();
    void prepareOverview();
    void prepareNextRound();
    void addAnswer(QString answer);
    void addPlayerAnswers(GameStats gs);
    void hostLobby();
    void joinLobby();
    void lobbySettingsChanged();
    void sendChatMessage(QString str);
    void triggerStateChange(int);
    void triggerStateRelatedSignal(STATE);
    void sendAnswers();

signals:
    void letterChanged();
    void categoriesChanged();
    void customCategoriesChanged();
    void answersChanged();
    void categoryCountChanged();
    void customCheckedChanged();
    void currentRoundChanged();
    void maxRoundsChanged();
    void pointsChanged();
    void timeLeftChanged();
    void lobbyCodeChanged();
    void playerCountChanged();
    void activeOverviewItemChanged();
    void decisionsChanged();
    void playersChanged();
    void viewChanged();
    void playerIdChanged();
    void playerNameChanged();
    void roundTimeChanged();
    void chatLogChanged();
    void answersRequest();

private:

    QString GetViewFromState(STATE);
    void AddChatMessage(const QString& sender,const QString& text);

    QString _letter             = "bad";
    QString _lobbyCode          = "";
    QString _customCategories   = "Stadt,Land,Fluss,Name,Tier,Beruf";
    QString _maxRounds          = "5";
    QString _roundTime          = "bis Stop";
    QString _timeLeft           = "bis Stop";
    QString m_customCategories  = {};
    QString _view               = "MainMenu";
    QString _playerName         = "";
    QString _chatLog            = "";
    StrVector _categories       = {"Stadt", "Land", "Fluss", "Name", "Tier", "Beruf"};
    StrVector _unhandledanswers = {};
    PlayerMap _players          = {};
    StrVector2D _answers        = {};
    int _categoryCount          = 6;
    int _currentRound           = 0;
    int _points                 = 999;
    int _playerCount            = 0;
    int _activeOverviewItem     = 0;
    int _playerId               = 0;
    DecVector2D _decisions      = {};
    bool _customChecked         = false;

};

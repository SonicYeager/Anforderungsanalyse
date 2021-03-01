#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#endif // QMLADAPTER_H
#include <QObject>
#include <vector>
#include <string>
#include <QAbstractListModel>
#include "UI.h"

using StrVector = std::vector<std::string>;

class QmlAdapter : public QObject, public UI
{
    Q_OBJECT
    Q_PROPERTY(QString letter              READ getLetter                WRITE setLetter                NOTIFY letterChanged)
    Q_PROPERTY(QString lobbyCode           READ getLobbyCode             WRITE setLobbyCode             NOTIFY lobbyCodeChanged)
    Q_PROPERTY(QString customCategories    READ getCustomCategories      WRITE setCustomCategories      NOTIFY customCategoriesChanged)
    Q_PROPERTY(QString maxRounds           READ getMaxRounds             WRITE setMaxRounds             NOTIFY maxRoundsChanged)
    Q_PROPERTY(QString timeLeft            READ getTimeLeft              WRITE setTimeLeft              NOTIFY timeLeftChanged)
    Q_PROPERTY(StrVector categories        READ getCategories            WRITE setCategories            NOTIFY categoriesChanged)
    Q_PROPERTY(StrVector answers           READ getAnswers               WRITE setAnswers               NOTIFY answersChanged)
    Q_PROPERTY(int categoryCount           READ getCategoryCount         WRITE setCategoryCount         NOTIFY categoryCountChanged)
    Q_PROPERTY(int currentRound            READ getCurrentRound          WRITE setCurrentRound          NOTIFY currentRoundChanged)
    Q_PROPERTY(int points                  READ getPoints                WRITE setPoints                NOTIFY pointsChanged)
    Q_PROPERTY(int activeOverviewItem      READ getActiveOverviewItem    WRITE setActiveOverviewItem    NOTIFY activeOverviewItemChanged)
    Q_PROPERTY(int playerCount             READ getPlayerCount           WRITE setPlayerCount           NOTIFY playerCountChanged)
    Q_PROPERTY(bool customChecked          READ getCustomChecked         WRITE setCustomChecked         NOTIFY customCheckedChanged)
    Q_PROPERTY(bool lobbyScreenVisible     READ getLobbyScreenVisible    WRITE setLobbyScreenVisible    NOTIFY lobbyScreenVisibleChanged)
    Q_PROPERTY(bool entryScreenVisible     READ getEntryScreenVisible    WRITE setEntryScreenVisible    NOTIFY entryScreenVisibleChanged)
    Q_PROPERTY(bool overviewScreenVisible  READ getOverviewScreenVisible WRITE setOverviewScreenVisible NOTIFY overviewScreenVisibleChanged)
    Q_PROPERTY(bool fscoresScreenVisible   READ getFScoresScreenVisible  WRITE setFScoresScreenVisible  NOTIFY fscoresScreenVisibleChanged)
    Q_PROPERTY(bool mainMenuScreenVisible  READ getMainMenuScreenVisible WRITE setMainMenuScreenVisible NOTIFY mainMenuScreenVisibleChanged)

public:
    explicit QmlAdapter     (QObject *parent = nullptr);

    void Init               (const GameStats&, const PlayerStats&) override;
    void PrepareGame        (const GameStats&, const PlayerStats&) override;
    void PrepareFinalScores (const GameStats&, const PlayerStats&) override;
    void PrepareOverview    (const GameStats&, const PlayerStats&) override;

    QString getLetter();
    QString getLobbyCode();
    QString getCustomCategories();
    QString getMaxRounds();
    QString getTimeLeft();
    StrVector getCategories();
    StrVector getAnswers();
    int getCategoryCount();
    int getCurrentRound();
    int getPoints();
    int getActiveOverviewItem();
    int getPlayerCount();
    bool getCustomChecked();
    bool getLobbyScreenVisible();
    bool getEntryScreenVisible();
    bool getOverviewScreenVisible();
    bool getFScoresScreenVisible();
    bool getMainMenuScreenVisible();


    void setLetter                      (QString letter);
    void setLobbyCode                   (QString lobbyCode);
    void setCustomCategories            (QString customCategories);
    void setTimeLeft                    (QString timeLeft);
    void setMaxRounds                   (QString maxRounds);
    void setCategories                  (StrVector categories);
    void setAnswers                     (StrVector answers);
    void setCategoryCount               (int categoryCount);
    void setCurrentRound                (int currentRound);
    void setPoints                      (int points);
    void setActiveOverviewItem          (int activeOverviewItem);
    void setPlayerCount                 (int playerCount);
    void setCustomChecked               (bool checked);
    void setLobbyScreenVisible          (bool visibility);
    void setEntryScreenVisible          (bool visibility);
    void setOverviewScreenVisible       (bool visibility);
    void setFScoresScreenVisible        (bool visibility);
    void setMainMenuScreenVisible       (bool visibility);

public slots:

    QString getCategoryName(int idx);
    QString getAnswer(int idx);
    DECISION getDecision(int idx);
    void setActiveItemIA(int idx);
    void setDecision(int idx, int newVal);
    void prepareGame();
    void prepareOverview();
    void prepareNextRound();
    void addAnswer(QString answer);

signals:
    void letterChanged();
    void categoriesChanged();
    void customCategoriesChanged();
    void answersChanged();
    void categoryCountChanged();
    void customCheckedChanged();
    void lobbyScreenVisibleChanged();
    void entryScreenVisibleChanged();
    void overviewScreenVisibleChanged();
    void fscoresScreenVisibleChanged();
    void mainMenuScreenVisibleChanged();
    void currentRoundChanged();
    void maxRoundsChanged();
    void pointsChanged();
    void timeLeftChanged();
    void lobbyCodeChanged();
    void playerCountChanged();
    void activeOverviewItemChanged();
    void decisionsChanged();

private:
    QString _letter             = "bad";
    QString _lobbyCode          = "0000";
    QString _customCategories   = "Stadt,Land,Fluss,Name,Tier,Beruf";
    QString _maxRounds          = "5";
    QString _timeLeft           = "bis Stop";
    QString m_customCategories  = {};
    StrVector _categories       = {"Stadt", "Land", "Fluss", "Name", "Tier", "Beruf"};
    StrVector _answers          = {};
    StrVector _unhandledanswers = {};
    int _categoryCount          = 6;
    int _currentRound           = 0;
    int _points                 = 999;
    int _playerCount            = 1;
    int _activeOverviewItem     = 0;
    std::vector<DECISION> _decisions = {DECISION::UNANSWERED,DECISION::UNANSWERED,DECISION::UNANSWERED,DECISION::UNANSWERED,DECISION::UNANSWERED,DECISION::UNANSWERED};
    bool _customChecked         = false;
    bool _lobbyScreenVisible    = false;
    bool _entryScreenVisible    = false;
    bool _overviewScreenVisible = false;
    bool _fscoresScreenVisible  = false;
    bool _mainMenuScreenVisible = true;
};

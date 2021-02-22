#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#endif // QMLADAPTER_H
#include <QObject>
#include <vector>
#include <string>
#include <QAbstractListModel>
#include "UI.h"

using Categories = std::vector<std::string>;

class QmlAdapter : public QObject, public UI
{
    Q_OBJECT
    Q_PROPERTY(QString letter           READ getLetter             WRITE setLetter             NOTIFY letterChanged)
    Q_PROPERTY(QString lobbyCode        READ getLobbyCode          WRITE setLobbyCode          NOTIFY lobbyCodeChanged)
    Q_PROPERTY(QString customCategories READ getCustomCategories   WRITE setCustomCategories   NOTIFY customCategoriesChanged)
    Q_PROPERTY(Categories categories    READ getCategories         WRITE setCategories         NOTIFY categoriesChanged)
    Q_PROPERTY(int categoryCount        READ getCategoryCount      WRITE setCategoryCount      NOTIFY categoryCountChanged)
    Q_PROPERTY(int currentRound         READ getCurrentRound       WRITE setCurrentRound       NOTIFY currentRoundChanged)
    Q_PROPERTY(QString maxRounds        READ getMaxRounds          WRITE setMaxRounds          NOTIFY maxRoundsChanged)
    Q_PROPERTY(int points               READ getPoints             WRITE setPoints             NOTIFY pointsChanged)
    Q_PROPERTY(QString timeLeft             READ getTimeLeft           WRITE setTimeLeft           NOTIFY timeLeftChanged)
    Q_PROPERTY(bool customChecked       READ getCustomChecked      WRITE setCustomChecked      NOTIFY customCheckedChanged)
    Q_PROPERTY(bool lobbyScreenVisible  READ getLobbyScreenVisible WRITE setLobbyScreenVisible NOTIFY lobbyScreenVisibleChanged)
    Q_PROPERTY(bool entryScreenVisible  READ getEntryScreenVisible WRITE setEntryScreenVisible NOTIFY entryScreenVisibleChanged)

public:
    explicit QmlAdapter(QObject *parent = nullptr);

    void Init(const GameStats&, const PlayerStats&) override;

    QString getLetter();
    QString getLobbyCode();
    QString getCustomCategories();
    Categories getCategories();
    bool getCustomChecked();
    bool getLobbyScreenVisible();
    bool getEntryScreenVisible();
    int getCategoryCount();
    int getCurrentRound();
    QString getMaxRounds();
    int getPoints();
    QString getTimeLeft();

    void setLetter(QString letter);
    void setLobbyCode(QString lobbyCode);
    void setCustomCategories(QString customCategories);
    void setCategories(Categories categories);
    void setCustomChecked(bool checked);
    void setLobbyScreenVisible(bool visibility);
    void setEntryScreenVisible(bool visibility);
    void setCategoryCount(int categoryCount);
    void setCurrentRound(int currentRound);
    void setMaxRounds(QString maxRounds);
    void setPoints(int points);
    void setTimeLeft(QString timeLeft);

public slots:
    QString getCategoryName(int idx);
    void prepareGame();

signals:
    void letterChanged();
    void categoriesChanged();
    void customCategoriesChanged();
    void categoryCountChanged();
    void customCheckedChanged();
    void lobbyScreenVisibleChanged();
    void entryScreenVisibleChanged();
    void currentRoundChanged();
    void maxRoundsChanged();
    void pointsChanged();
    void timeLeftChanged();
    void lobbyCodeChanged();

private:
    QString _letter = "C";
    QString _lobbyCode = "0000";
    QString _customCategories = "Stadt, Land, Fluss, Name, Tier, Beruf";
    int _categoryCount = 3;
    int _currentRound = 0;
    QString _maxRounds = "5";
    int _points = 999;
    QString _timeLeft = "bis Stop";
    bool _customChecked = false;
    bool _lobbyScreenVisible = true;
    bool _entryScreenVisible = false;
    Categories _categories = {"Stadt", "Land", "Fluss", "Name", "Tier", "Beruf"};
    GameStats _gs;
    PlayerStats _ps;
    QString m_customCategories;
};

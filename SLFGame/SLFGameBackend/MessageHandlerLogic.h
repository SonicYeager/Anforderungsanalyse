#pragma once
#include "Messages.h"

using namespace Messages;

class MessageHandlerLogic {
public:
	virtual void handleMessage(const Message&) = 0;
	virtual void on(const Playername&) = 0;
	virtual void on(const PlayerID&) = 0;
	virtual void on(const PlayerAnswers&) = 0;
	virtual void on(const HandleGameSettings&) = 0;
	virtual void on(const GameState&) = 0;

	Event<Playername> onPlayername;
	Event<PlayerID> onPlayerID;
	Event<PlayerAnswers> onPlayerAnswers;
	Event<HandleGameSettings> onHandleGameSettings;
	Event<GameState> onGameState;
};
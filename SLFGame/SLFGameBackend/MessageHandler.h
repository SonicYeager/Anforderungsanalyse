#pragma once
#include "MessageHandlerLogic.h"

class MessageHandler : public MessageHandlerLogic {
public:
	void handleMessage(const Message&) override;
	void on(const Playername&) override;
	void on(const PlayerID&) override;
	void on(const PlayerAnswers&) override;
	void on(const HandleGameSettings&) override;
	void on(const GameState&) override;
	void on(const ChatMessage&) override;
	void on(const AllAnswers&) override;
};
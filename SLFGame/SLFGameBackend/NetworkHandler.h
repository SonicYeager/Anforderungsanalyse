#include "DataTypes.h"
#include "Messages.h"
#include <variant>
#include "NetworkHandlerLogic.h"


class MessageHandler : public NetworkHandlerLogic {
public:
	void handleMessage(Messages::Message msg, NetworkData data) override;
	void on(Messages::HandleGameStats pl, NetworkData data) override;
	void on(Messages::Alternative pl, NetworkData data) override;

	Event<Messages::HandleGameStats, NetworkData> onGet;
	Event<Messages::Alternative, NetworkData> onSet;
};
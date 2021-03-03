#pragma once
#include "Serializer.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class QDataSerializer : public Serializer
{
public:
	QByteArray Serialize(const NetworkData&) override;
	NetworkData Deserialize(const QByteArray&) override;
};
#pragma once
#include "DataTypes.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class Serializer
{
public:
	virtual ~Serializer() = default;

	virtual QByteArray Serialize(const NetworkData&) = 0;
	virtual NetworkData Deserialize(const QByteArray&) = 0;
};
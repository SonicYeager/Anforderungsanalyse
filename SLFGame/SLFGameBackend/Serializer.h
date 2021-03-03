#pragma once
#include "DataTypes.h"

using QByteArray = class QByteArray;

class Serializer
{
public:
	virtual ~Serializer() = default;

	virtual QByteArray Serialize(const NetworkData&) = 0;
	virtual NetworkData Deserialize(const QByteArray&) = 0;
};
#pragma once
#include "Serializer.h"

class QDataSerializer : public Serializer
{
public:
	virtual QDataStream Serialize(const NetworkData&) = 0;
	virtual NetworkData Deserialize(const QDataStream&) = 0;
};
#pragma once
#include "DataTypes.h"

#define QPROPERTY_SIGNAL(type, name) void name##_changed ();

#define QPROPERTY_SETTER(type, name) \
	void  set_##name(type val) \
	{ \
		    if (val == _##name)	\
				return; \
			_##name = val; \
			emit name##_changed();  \
	}

#define QPROPERTY_GETTER(type, name) \
	type get_##name() \
	{ \
		return _##name; \
	}


#define QPROPERTY_AUTO(type, name) \
	private: \
		Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##_changed) \
	public: \
		QPROPERTY_GETTER(type, name) \
		QPROPERTY_SETTER(type, name) 
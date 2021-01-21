#pragma once
#include <string>

class Interactor
{
public:
	virtual std::string InitApp(/*show dlg and set time event*/) = 0;
};
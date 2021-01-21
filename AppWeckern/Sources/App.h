#pragma once
#include "Interactor.h"
#include "UI.h"

class App
{
public:
	explicit App(UI&, Interactor&);
	void Run();

private:
	UI& p_ui;
	Interactor& p_inter;
};

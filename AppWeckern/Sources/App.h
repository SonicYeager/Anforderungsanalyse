#pragma once
#include "Interactor.h"
#include "UI.h"

class App
{
public:
	explicit App(UI&, Interactor&);
	void Run();

private:
	UI& ui;
	Interactor& inter;
};

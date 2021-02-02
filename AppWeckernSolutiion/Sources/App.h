#pragma once

namespace Wecker
{
	class UI;
	class Interactor;

	class App
	{
	public:
		App(UI*, Interactor*);

		void Run();

	private:
		UI* m_pUI;
		Interactor* m_pInteractor;
	};
} // namespace Wecker

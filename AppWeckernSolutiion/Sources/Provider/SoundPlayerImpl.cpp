#include "SoundPlayerImpl.h"
#include <windows.h>

namespace Wecker
{
	void SoundPlayerImpl::Play()
	{
		PlaySoundA("weckton.wav", nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}

	void SoundPlayerImpl::Stop()
	{
		PlaySoundA(nullptr, nullptr, 0);
	}
} // namespace Wecker

#include "AudioPlayer.h"
#include "Windows.h"
#include "mmsystem.h"

void AudioPlayer::PlayAudioFile(const std::filesystem::path& path)
{
	auto absolute = std::filesystem::absolute(path);
	std::wstring pathstr = path;
	auto worked = PlaySoundA(LPCSTR(pathstr.c_str()), NULL, SND_ASYNC);
}

#pragma once
#include "MediaRessource.h"

class AudioPlayer : public MediaRessource
{
public:
	void PlayAudioFile(const std::filesystem::path&) override;
};
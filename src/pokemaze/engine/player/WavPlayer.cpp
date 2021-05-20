#include "pokemaze/engine/player/WavPlayer.hpp"

#include <windows.h>
#include <mmsystem.h>


WavPlayer::WavPlayer(std::string music_file)
{
    this->music_file = music_file;
}

void WavPlayer::play()
{
    PlaySound(music_file.c_str(), NULL, SND_LOOP | SND_ASYNC);
}

void WavPlayer::stop()
{
    PlaySound(NULL, NULL,SND_SYNC);
}

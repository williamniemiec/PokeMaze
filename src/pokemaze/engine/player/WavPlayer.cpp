#include "pokemaze/engine/player/WavPlayer.hpp"

//#include <windows.h>
//#include <mmsystem.h>

using namespace pokemaze::engine::player;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
WavPlayer::WavPlayer(std::string music_file)
{
    this->music_file = music_file;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void WavPlayer::play()
{
    //PlaySound(music_file.c_str(), NULL, SND_LOOP | SND_ASYNC);
}

void WavPlayer::stop()
{
    //PlaySound(NULL, NULL,SND_SYNC);
}

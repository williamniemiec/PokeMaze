#include "pokemaze/engine/player/WavPlayer.hpp"

using namespace pokemaze::engine::player;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
WavPlayer::WavPlayer(std::string music_file)
{
    this->music_file = music_file;
    this->music.openFromFile(music_file);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void WavPlayer::play()
{
    music.play();
}

void WavPlayer::stop()
{
    music.stop();
}

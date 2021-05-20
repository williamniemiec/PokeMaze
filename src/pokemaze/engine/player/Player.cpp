#include "pokemaze/engine/player/Player.hpp"

#include <windows.h>
#include <mmsystem.h>

void Player::play(std::string filepath)
{
    PlaySound(filepath.c_str(), NULL, SND_LOOP | SND_ASYNC);
}

void Player::stop()
{
    PlaySound(NULL, NULL,SND_SYNC);
}

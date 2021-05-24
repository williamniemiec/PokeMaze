#pragma once

#include <iostream>

namespace pokemaze {namespace engine {namespace player {
    class WavPlayer
    {
    public:
        std::string music_file;
    public:
        WavPlayer(std::string filepath);
    public:
        void play();
        void stop();
    };
}}}

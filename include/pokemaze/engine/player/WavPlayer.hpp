#pragma once

#include <iostream>

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

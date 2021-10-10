#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

namespace pokemaze { namespace engine { namespace player {

    /**
     * Responsible for playing wav files.
     */
    class WavPlayer
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        std::string music_file;
        sf::Music music;

    
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Wav files player.
         * 
         * @param       filepath Wav file path
         */
        WavPlayer(std::string filepath);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Plays wav file.
         */
        void play();

        /**
         * Stops wav file.
         */
        void stop();
    };
}}}

#pragma once

#include <iostream>

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

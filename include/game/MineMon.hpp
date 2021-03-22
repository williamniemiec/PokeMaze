#pragma once

namespace game
{
    class MineMon
    {
    private:
        bool stopGame;

    public:
        MineMon();

    public:
        void start();
    private:
        void run();
        void quit();
    };
}

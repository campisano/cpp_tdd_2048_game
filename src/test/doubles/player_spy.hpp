#ifndef PLAYER_SPY__HPP__
#define PLAYER_SPY__HPP__

#include "../../2048/domain/player.hpp"

class PlayerSpy : public Player
{
public:
    int       chooseDirection_calls = 0;
    Direction chooseDirection_out;
    Direction chooseDirection()
    {
        ++chooseDirection_calls;
        return chooseDirection_out;
    }
};

#endif

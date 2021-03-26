#ifndef PLAYER_SPY__HPP__
#define PLAYER_SPY__HPP__

#include <memory>
#include "../../../2048/domain/player.hpp"

class PlayerSpy : public Player
{
public:
    using Movable = std::unique_ptr<Player>;

    int       chooseDirection_calls = 0;
    Direction chooseDirection_out;
    Direction chooseDirection()
    {
        ++chooseDirection_calls;
        return chooseDirection_out;
    }
};

#endif

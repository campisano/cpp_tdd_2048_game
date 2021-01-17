#ifndef PLAYER__HPP__
#define PLAYER__HPP__

#include <memory>
#include "direction.hpp"

class Player
{
public:
    using Movable = std::unique_ptr<Player>;

public:
    explicit Player()      = default;
    Player(const Player &) = delete;
    Player(Player &&)      = default;
    virtual ~Player()      = default;

    Player & operator=(const Player &) = delete;
    Player & operator=(Player &&)      = default;

public:
    virtual Direction makeSlide() = 0;
};

#endif

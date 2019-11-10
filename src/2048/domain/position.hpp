#ifndef POSITION__HPP__
#define POSITION__HPP__

class Position
{
public:
    explicit Position();
    Position(const Position &) = delete;
    Position(Position &&) = default;
    virtual ~Position();

    Position & operator=(const Position &) = delete;
    Position & operator=(Position &&) = default;

public:

private:
};

#endif

#ifndef MOVE_USECASE_PORT__HPP__
#define MOVE_USECASE_PORT__HPP__

class MoveUsecasePort
{
public:
    enum class Direction { left, right, up, down };

    virtual ~MoveUsecasePort() = default;

    virtual void execute(Direction & _direction) = 0;
};

#endif

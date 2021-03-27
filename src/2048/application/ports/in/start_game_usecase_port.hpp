#ifndef START_GAME_USECASE_PORT__HPP__
#define START_GAME_USECASE_PORT__HPP__

class StartGameUsecasePort
{
public:
    virtual ~StartGameUsecasePort() = default;

    virtual void execute(int _score, int _rows, int _cols) = 0;
};

#endif

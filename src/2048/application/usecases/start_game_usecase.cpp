#include "start_game_usecase.hpp"

StartGameUsecase::Movable StartGameUsecase::make(GameRepository & _grp,
        Player & _ply, Observer & _obs)
{
    return Movable(new StartGameUsecase(_grp, _ply, _obs));
}

StartGameUsecase::StartGameUsecase(
    GameRepository & _grp, Player & _ply, Observer & _obs):
    m_grp(_grp), m_ply(_ply), m_obs(_obs)
{
}

StartGameUsecase::~StartGameUsecase()
{
}

void StartGameUsecase::execute(int _score, int _rows, int _cols)
{
    auto board = Board::make(_rows, _cols);
    auto game  = m_grp.create(_score, board, m_ply, m_obs);

    game->start();
}

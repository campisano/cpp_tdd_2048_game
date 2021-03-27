#include "start_game_usecase.hpp"

#include "../../domain/board.hpp"

StartGameUsecase::Movable StartGameUsecase::make(
    GameRepositoryPort & _game_repo,
    PlayerRepositoryPort & _player_repo,
    Observer & _observer)
{
    return Movable(new StartGameUsecase(_game_repo, _player_repo, _observer));
}

StartGameUsecase::StartGameUsecase(
    GameRepositoryPort & _game_repo,
    PlayerRepositoryPort & _player_repo,
    Observer & _observer)
    : m_game_repo(_game_repo), m_player_repo(_player_repo), m_observer(_observer)
{
}

StartGameUsecase::~StartGameUsecase()
{
}

void StartGameUsecase::execute(int _score, int _rows, int _cols)
{
    {
        auto player = HumanPlayer::make();
        m_player_repo.saveCurrent(player);
    }

    {
        auto & player = m_player_repo.getCurrent();
        auto board    = Board::make(_rows, _cols);
        auto game     = SpawnGame::make(_score, board, player, m_observer);
        m_game_repo.saveCurrent(game);
    }

    auto & game = m_game_repo.getCurrent();
    game.spawn();
}

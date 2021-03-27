#include <iostream>
#include <stdexcept>
#include "2048/adapters/console_controller.hpp"
#include "2048/adapters/console_observer.hpp"
#include "2048/adapters/game_repository.hpp"
#include "2048/adapters/player_repository.hpp"
#include "2048/application/usecases/move_usecase.hpp"
#include "2048/application/usecases/start_game_usecase.hpp"

int main(int, char **)
{
    try
    {
        PlayerRepository player_repo;
        GameRepository   game_repo;
        ConsoleObserver  observer;

        // TODO observer repository?
        auto start_usecase = StartGameUsecase::make(game_repo, player_repo, observer);
        auto move_usecase  = MoveUsecase::make(player_repo);

        ConsoleController c(*start_usecase, *move_usecase);
        c.start();

        // TODO to move inside controller... but how? console does not know current game or repository...
        // who should know that the game is spawn and should wait for it ends?
        game_repo.getCurrent().join();
    }
    catch(std::exception const & _ex)
    {
        std::cerr << "Error: " << _ex.what() << std::endl;
        throw;
    }

    return EXIT_SUCCESS;
}

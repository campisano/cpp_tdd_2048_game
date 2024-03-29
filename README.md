[![Build Status](https://gitlab.com/campisano/cpp_tdd_2048_game/badges/master/pipeline.svg "Build Status")](https://gitlab.com/campisano/cpp_tdd_2048_game/-/pipelines)
[![Sonar Coverage](https://sonarcloud.io/api/project_badges/measure?project=cpp_tdd_2048_game&metric=coverage "Sonar Coverage")](https://sonarcloud.io/dashboard?id=cpp_tdd_2048_game)
[![Sonar Maintainability](https://sonarcloud.io/api/project_badges/measure?project=cpp_tdd_2048_game&metric=sqale_rating "Sonar Maintainability")](https://sonarcloud.io/dashboard?id=cpp_tdd_2048_game)
[![Docker Image](https://img.shields.io/docker/image-size/riccardocampisano/public/cpp_tdd_2048_game-latest?label=cpp_tdd_2048_game-latest&logo=docker "Docker Image")](https://hub.docker.com/r/riccardocampisano/public/tags?name=cpp_tdd_2048_game)

# 2048 Game

Game description in https://en.wikipedia.org/wiki/2048_(video_game)#Gameplay

# Test Specs

## Business rules

1) There is a board:
    - board is a set of positions organized in rows and columns (e.g. 16 positions in a 4 rows and 4 columns);
    - a board can not have less than 2 positins, less than 2 rows and less than 2 columns;
    - player can make a slide in one direction {left,right,up,down}:
        - a slide is applied to all the numbers in the board, starting from the nearest to the destination of the slide;
        - a sliding number will stop when encounter a board edge or a number that cannot be merged;
        - if a sliding number encounters a number that can be merged, it will be merged in the number and the sliding number will be removed from the board;
        - if a sliding number encounter a number that was already merged, it must stop;
    - a number can be placed randomly in a board empty position.

0) There are numbers:
    - a number has a value;
    - a value must be greater than or equal to 2;
    - a value must be power of two;
    - a number A can merge in another number B with the same value:
        - the B number will became merged and will have the double of its original value;
        - the A number will be removed from its original place.

0) There are positions:
    - a position can have a number placed on itself;
    - a position can have adiacent positions {left,right,up,down}.

0) There is a player:
    - a player is queried for a valid direction to slide.

0) There is a game:
    - at every turn, a random number (with value of 2 or 4) is placed in a random empty spot of the board;
    - at every turn, a valid slide direction is requested to the player;
    - game ends when player win (when obtain a 2048 number) or lose (when can not slide due to end of spaces and mergeable slides in the board).

0) There is an observer:
    - an observer is notified about game events (start, number placed, player slided, end).

## Use cases

1) A player starts a new game:
    - the player defines the end score and the board size;
    - the game validates the board size;
    - the game notifies the start with winning score and board size;
    - the game places a number;
    - the game notifies the number value and position.

2) The playar make a slide:

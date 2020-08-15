[![Build Status](https://travis-ci.org/campisano/cpp_tdd_2048_game.svg?branch=master "Build Status")](https://travis-ci.org/campisano/cpp_tdd_2048_game)
[![Test Coverage](https://codecov.io/gh/campisano/cpp_tdd_2048_game/branch/master/graph/badge.svg "Test Coverage")](https://codecov.io/gh/campisano/cpp_tdd_2048_game)
[![Code Quality](https://img.shields.io/lgtm/grade/cpp/g/campisano/cpp_tdd_2048_game.svg "Code Quality")](https://lgtm.com/projects/g/campisano/cpp_tdd_2048_game/context:cpp)
[![Sonar Coverage](https://sonarcloud.io/api/project_badges/measure?project=campisano/cpp_tdd_2048_game&metric=coverage)](https://sonarcloud.io/dashboard?id=campisano/cpp_tdd_2048_game)
[![Sonar Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=campisano/cpp_tdd_2048_game&metric=alert_status)](https://sonarcloud.io/dashboard?id=campisano/cpp_tdd_2048_game)

[![Docker Hub](https://img.shields.io/docker/image-size/riccardocampisano/public/cpp_tdd_2048_game-latest?label=cpp_tdd_2048_game-latest&logo=docker)](https://hub.docker.com/r/riccardocampisano/public/tags?name=cpp_tdd_2048_game)

# 2048 Game

Game description in https://en.wikipedia.org/wiki/2048_(video_game)#Gameplay

# Test Specs

1) There is a board:
    - board is divided in 16 positions (four-by-four);
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

0) There is a game:
    - at every turn, a random number, with value of 2 or 4, is placed in a random empty spot of the board

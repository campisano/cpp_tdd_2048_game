# 2048 Game [![Build Status][ci_img]][ci_link] [![Language grade: C/C++][cq_img]][cq_link]
[ci_link]: https://travis-ci.org/campisano/cpp_tdd_2048_game
[ci_img]: https://travis-ci.org/campisano/cpp_tdd_2048_game.svg?branch=master "Continuous Integration"
[cq_link]: https://lgtm.com/projects/g/campisano/cpp_tdd_2048_game/context:cpp
[cq_img]: https://img.shields.io/lgtm/grade/cpp/g/campisano/cpp_tdd_2048_game.svg?logo=lgtm&logoWidth=18 "Code Quality"

Game description in https://en.wikipedia.org/wiki/2048_(video_game)#Gameplay

# Test Specs

1) There is a board:
    - board is divided in 16 positions (four-by-four);
    - board positions are arranged inside the board borders;
    - player can make a slide in one direction {left,right,up,down}:
        - a slide is applied to all the numbers in the board, starting from the nearest to the destination of the slide;
        - a sliding number will stop when encounter a board border or a number that cannot be merged;
        - if a sliding number encounters a number that can be merged, it will be merged in the number and the sliding number will be removed from the board;
        - if a sliding number encounter a number that was already merged, it must stop.
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

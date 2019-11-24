# 2048 Game [![Build Status][ci_img]][ci_link] [![Language grade: C/C++][cq_img]][cq_link]
[ci_link]: https://travis-ci.org/campisano/cpp_tdd_2048_game
[ci_img]: https://travis-ci.org/campisano/cpp_tdd_2048_game.svg?branch=master "Continuous Integration"
[cq_link]: https://lgtm.com/projects/g/campisano/cpp_tdd_2048_game/context:cpp
[cq_img]: https://img.shields.io/lgtm/grade/cpp/g/campisano/cpp_tdd_2048_game.svg?logo=lgtm&logoWidth=18 "Code Quality"

https://en.wikipedia.org/wiki/2048_(video_game)#Gameplay

There are numbers in a board. The position of the number appears to be a important thing. Numbers will move all together, according to the move direction. When the player chose a move direction, for each number, the position at the chosen direction nearby the number is evaluated. If it is free, the number move at that position and still does not stop there, because it will move until there is a condition to stop. The number will stop if it will encounter the border of the board, or if it will encounter a number that can not be merge with itself. A moving number can merge with an another if the other number is stopped and was not merged.

# Test Specs

1) there is a board
    - board is divided in 16 positions (four-by-four)
    - board positions are arranged inside its borders
    - player can make a slide in one direction {left,right,up,down}
        - the slide is applied at all the number in the board, starting from the nearest to the destination of the slide
        - a sliding number will stop when encounter a board border or a number that can not be merged
        - if a sliding number encounter a number that can be merged, it will be merged in the number and will be removed from the board
        - if a sliding number encounter a number that was already merged, it must stop
0) there are numbers
    - number has a value
    - value must be greater than or equal to 2
    - value must be power of two
    - a number A can merge in another B number with the same value
        - the B number will have the merge status and the double of its original value
        - the A number will be removed from its original place
0) there are positions
    - position can have a number placed on itself
    - position can have adiacent positions {left,right,up,down}

//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_DISPLAYGAME_H
#define EX2_DISPLAYGAME_H

#include "Board.h"
#include <string>
#include <iostream>
using namespace std;

/**
 * abstract class DisplayGame
 */
class DisplayGame {
public:

    /**
     * constructor of DisplayGame object.
     * @param board
     */
    DisplayGame(Board *board): board(board){}
    /**
     * printGameBoard function will print the board as requested.
     */
    virtual void printGameBoard() const = 0;
    /**
     * destructor of DisplayGame object
     */
    virtual ~DisplayGame(){}

protected:
    //pointer to the game's board
    Board *board;
};

#endif //EX2_DISPLAYGAME_H
